#include "Commando.h"
#include "BaseAttackBullet.h"

#include "../Object/Tile.h"
#include "../StageManager.h"

#include "../stdafx.h"
#include "../Input.h"
#include "../Camera.h"
#include "../StageManager.h"

#include "../Object/Tile.h"
#include "../Object/Bar.h"
#include "../Object/Number.h"
#include "../Object/ExpEffect.h"
#include "../Object/ItemBox.h"
#include "../Object/IssacTear.h"

#include "../Object/AncientHitBox.h"
#include "../Object/JellyFishHitBox.h"

#include "../Resource/Animation.h"

#include "../Coll/ColliderRect.h"
#include "../Coll/ColliderPoint.h"

#include "../Scene/Scene.h"
#include "../Scene/Layer.h"

#include "../Object/Hider.h"

#include "../Sound/SoundManager.h"

void Commando::TileCollsionActive(float DeltaTime)
{
	if (isJumping == true)
		isJumping = false;
}

void Commando::BulletHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "BulletBody")
	{
		Object*	newBullet = Dest->GetCurObject();
		newBullet->SetisActiv(false);
		SAFE_RELEASE(newBullet);
	}
}
void Commando::RopeHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "RopeBody")
	{
		if (KEYPRESS("Up") == false && KEYPRESS("Down") == false && pState != PS_ROPE)
			return;

		isRopeHiting = true;
		RopePos = Dest->GetPos();
	}
}

void Commando::RopeUpHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "RopeBody")
	{
		isRopeUpHitting = true;
	}
}

void Commando::PumpHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "PumpBody")
	{
		SetForce(1200.0f);
		isJumping = true;
		SelectState(PLAYER_STATE::PS_JUMPING);
	}
}

void Commando::CoinHit(Collider* Src, Collider* Dest, float DeltaTime)
{
	if (Dest->GetTag() == "CoinBody")
	{
		Object* pObject = Dest->GetCurObject();

		if (pObject->GetObjectType() == OT_COIN)
		{
			pMoney += 8;
			pObject->SetisActiv(false);
		}
		else if (pObject->GetObjectType() == OT_EXP)
		{
			Exp += 10;

			ExpEffect* newEffect = (ExpEffect*)Object::CreateCloneObject("ExpEffect", m_Layer);
			newEffect->SetPos(m_Pos);

			SAFE_RELEASE(newEffect);
			pObject->SetisActiv(false);
		}
		SAFE_RELEASE(pObject);
	}
}

void Commando::ItemBoxHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "ItemBoxBody")
	{
		ItemBox* getBox = (ItemBox*)Dest->GetCurObject();

		if (KEYDown('A'))
		{
			if (pMoney >= getBox->GetPrice())
			{
				pMoney -= getBox->GetPrice();
				getBox->ChangeClip("ItemBoxOpen");
				SoundManager::Get()->Play("BoxOpen");
			}
		}

		SAFE_RELEASE(getBox);
	}
}

void Commando::TearHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "TearBody")
	{
		IssacTear* getTear = (IssacTear*)Dest->GetCurObject();

		if(pState != PS_SKILL3)
			Hp -= getTear->GetAttack();

		getTear->SetisActiv(false);

		SAFE_RELEASE(getTear);
	}
}

void Commando::AncientHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "AcientHitBody")
	{
		AncientHitBox* getBox = (AncientHitBox*)Dest->GetCurObject();

		Hp -= getBox->GetAttack();

		getBox->SetisActiv(false);

		SAFE_RELEASE(getBox);
	}
}

void Commando::JellyFishHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "JellyFishHit")
	{
		JellyFishHitBox* getBox = (JellyFishHitBox*)Dest->GetCurObject();

		Hp -= getBox->GetAttack();

		SAFE_RELEASE(getBox);
	}
}

void Commando::LineHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "MonsterBody")
	{
		HitSize = ((ColliderRect*)Dest)->GetSize();
		HitPos = Dest->GetPos();

		HitPosList.push_back(HitPos);

		list<Vector2>::iterator StartIter = HitPosList.begin();
		list<Vector2>::iterator EndIter = HitPosList.end();

		for(; StartIter != EndIter; StartIter++)
		{
			float a = Math::GetDistance(m_Pos, HitPos);
			float b = Math::GetDistance(m_Pos, *StartIter);

			if (a > b)
				HitPos = *StartIter;
		}

		isLineHit = true;
	}
}