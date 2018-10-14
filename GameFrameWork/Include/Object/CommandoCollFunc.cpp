#include "Commando.h"
#include "BaseAttackBullet.h"
#include "../Sound/SoundManager.h"
#include "../Resource/Animation.h"
#include "../StageManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/Scene.h"
#include "../Scene/Layer.h"
#include "../stdafx.h"
#include "../Input.h"
#include "../Camera.h"
#include "../StageManager.h"
#include "../Resource/Animation.h"
#include "../Object/Tile.h"
#include "../Object/Bar.h"
#include "../Object/Number.h"
#include "../Object/ExpEffect.h"
#include "../Object/ItemBox.h"
#include "../Object/IssacTear.h"
#include "../Object/Colossus.h"
#include "../Object/AncientHitBox.h"
#include "../Object/JellyFishHitBox.h"
#include "../Object/LemurinHitBox.h"
#include "../Object/WispHitBox.h"
#include "../Object/RockGolenHitBox.h"
#include "../Object/ColossusClapHitBox.h"
#include "../Object/ColossusKickHitBox.h"
#include "../Object/Tile.h"
#include "../Object/Hider.h"
#include "../Object/UsingItemBase.h"
#include "../Object/ItemBase.h"
#include "../Object/ItemBooster.h"

#include "../Coll/ColliderRect.h"
#include "../Coll/ColliderPoint.h"

void Commando::TileCollsionActive(float DeltaTime)
{
	if (isJumping == true)
		isJumping = false;
}

void Commando::TelePoterHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "TelePoterBody")
	{
		if (KEYDown('A'))
		{
			if (MainScene::GetStageOneBoss() == true)
				return;

			Colossus* newBoss = Object::CreateObject<Colossus>("Colossus", m_Layer);
			newBoss->SetPos(Dest->GetPos().x, Dest->GetPos().y - newBoss->GetSize().GetHalfY());

			MainScene::SetStageOneBoss(true);

			SoundManager::Get()->Play("Recive");
			SoundManager::Get()->Stop("BGM");
			SoundManager::Get()->Play("DNF", true);

			SAFE_RELEASE(newBoss);
		}
	}
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
			if (getBox->GetIsEnd() == true)
				return;

			if (pMoney >= getBox->GetPrice())
			{
				pMoney -= getBox->GetPrice();
				getBox->ChangeClip("ItemBoxOpen");
				SoundManager::Get()->Play("BoxOpen");

				ItemBooster* newBoost = Object::CreateObject<ItemBooster>("ItemBooster", m_Layer);
				newBoost->SetPos(Dest->GetPos().x, Dest->GetPos().y - 10.0f);
				newBoost->SetTempPos(Vector2(Dest->GetPos().x, Dest->GetPos().y - 10.0f));

				SAFE_RELEASE(newBoost);

				//int RandNumber = Math::RandomRange(0 , ItemBase::ITEM_KIND::ITEM_MAX);
				//switch (RandNumber)
				//{
				//	case ItemBase::ITEM_KIND::ITEM_BOOSTER:
				//	{
				//		ItemBooster* newBoost = Object::CreateObject<ItemBooster>("ItemBooster", m_Layer);
				//		newBoost->SetPos(Dest->GetPos().x , Dest->GetPos().y - 10.0f);

				//		SAFE_RELEASE(newBoost);
				//	}
				//		break;
				//	case ItemBase::ITEM_KIND::ITEM_ALIENHEAD:
				//		break;
				//	case ItemBase::ITEM_KIND::ITEM_FIREMANBOOT:
				//		break;
				//	case ItemBase::ITEM_KIND::ITEM_FIRESHIELD:
				//		break;
				//	case ItemBase::ITEM_KIND::ITEM_KNIFE:
				//		break;
				//	case ItemBase::ITEM_KIND::ITEM_TASER:
				//		break;
				//	case ItemBase::ITEM_KIND::ITEM_TELESCOPE:
				//		break;
				//	case ItemBase::ITEM_KIND::ITEM_TOUGHTIME:
				//		break;
				//}//switch
			}//if(Money)
		} //if(KeyDown)

		SAFE_RELEASE(getBox);
	} //if(Dest->GetTag)
}

void Commando::TearHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "TearBody")
	{
		IssacTear* getTear = (IssacTear*)Dest->GetCurObject();

		if (pState != PS_SKILL3 && isInfinity == false)
		{
			Hp -= getTear->GetAttack();

			Number* DamegaNumber = Object::CreateObject<Number>("DamegaNumber", m_Layer);
			DamegaNumber->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
			DamegaNumber->SetTexture("DamNumber", TEXT("object/BlueNumber.bmp"));
			DamegaNumber->SetNumberSize(19.0f, 24.0f);
			DamegaNumber->SetNumber(getTear->GetAttack());
			DamegaNumber->SetNumberViewSize(10.0f, 13.0f);
			DamegaNumber->SetMaxRange(50.0f, 100.0f);
			DamegaNumber->SetIsCameraMode(true);

			SAFE_RELEASE(DamegaNumber);
			isInfinity = true;
		}
		else if(pState == PS_SKILL3)
			SoundManager::Get()->Play("Miss");

		getTear->SetisActiv(false);

		SAFE_RELEASE(getTear);
	}
}

void Commando::AncientHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "AcientHitBody")
	{
		AncientHitBox* getBox = (AncientHitBox*)Dest->GetCurObject();
		
		if (pState != PS_SKILL3 && isInfinity == false)
		{
			Hp -= getBox->GetAttack();

			Number* DamegaNumber = Object::CreateObject<Number>("DamegaNumber", m_Layer);
			DamegaNumber->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
			DamegaNumber->SetTexture("DamNumber", TEXT("object/BlueNumber.bmp"));
			DamegaNumber->SetNumberSize(19.0f, 24.0f);
			DamegaNumber->SetNumber(getBox->GetAttack());
			DamegaNumber->SetNumberViewSize(10.0f, 13.0f);
			DamegaNumber->SetMaxRange(50.0f, 100.0f);
			DamegaNumber->SetIsCameraMode(true);

			SAFE_RELEASE(DamegaNumber);
			isInfinity = true;
		}
		else if(pState == PS_SKILL3)
			SoundManager::Get()->Play("Miss");

		getBox->SetisActiv(false);

		SAFE_RELEASE(getBox);
	}
}

void Commando::JellyFishHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "JellyFishHit")
	{
		JellyFishHitBox* getBox = (JellyFishHitBox*)Dest->GetCurObject();

		if (pState != PS_SKILL3 && isInfinity == false)
		{
			Hp -= getBox->GetAttack();

			Number* DamegaNumber = Object::CreateObject<Number>("DamegaNumber", m_Layer);
			DamegaNumber->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
			DamegaNumber->SetTexture("DamNumber", TEXT("object/BlueNumber.bmp"));
			DamegaNumber->SetNumberSize(19.0f, 24.0f);
			DamegaNumber->SetNumber(getBox->GetAttack());
			DamegaNumber->SetNumberViewSize(10.0f, 13.0f);
			DamegaNumber->SetMaxRange(50.0f, 100.0f);
			DamegaNumber->SetIsCameraMode(true);

			SAFE_RELEASE(DamegaNumber);
			isInfinity = true;
		}
		else if(pState == PS_SKILL3)
			SoundManager::Get()->Play("Miss");

		getBox->SetisActiv(false);

		SAFE_RELEASE(getBox);
	}
}

void Commando::LemuiranHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "LemurianHit")
	{
		LemurinHitBox* getBox = (LemurinHitBox*)Dest->GetCurObject();

		if (pState != PS_SKILL3 && isInfinity == false)
		{
			Hp -= getBox->GetAttack();

			Number* DamegaNumber = Object::CreateObject<Number>("DamegaNumber", m_Layer);
			DamegaNumber->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
			DamegaNumber->SetTexture("DamNumber", TEXT("object/BlueNumber.bmp"));
			DamegaNumber->SetNumberSize(19.0f, 24.0f);
			DamegaNumber->SetNumber(getBox->GetAttack());
			DamegaNumber->SetNumberViewSize(10.0f, 13.0f);
			DamegaNumber->SetMaxRange(50.0f, 100.0f);
			DamegaNumber->SetIsCameraMode(true);

			SAFE_RELEASE(DamegaNumber);
			isInfinity = true;

		}
		else if(pState == PS_SKILL3)
			SoundManager::Get()->Play("Miss");

		getBox->SetisActiv(false);

		SAFE_RELEASE(getBox);
	}
}

void Commando::WispHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "WispHit")
	{
		WispHitBox* getBox = (WispHitBox*)Dest->GetCurObject();

		if (pState != PS_SKILL3 && isInfinity == false)
		{
			Hp -= getBox->GetAttack();

			Number* DamegaNumber = Object::CreateObject<Number>("DamegaNumber", m_Layer);
			DamegaNumber->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
			DamegaNumber->SetTexture("DamNumber", TEXT("object/BlueNumber.bmp"));
			DamegaNumber->SetNumberSize(19.0f, 24.0f);
			DamegaNumber->SetNumber(getBox->GetAttack());
			DamegaNumber->SetNumberViewSize(10.0f, 13.0f);
			DamegaNumber->SetMaxRange(50.0f, 100.0f);
			DamegaNumber->SetIsCameraMode(true);

			SAFE_RELEASE(DamegaNumber);
			isInfinity = true;

		}
		else if(pState == PS_SKILL3)
			SoundManager::Get()->Play("Miss");

		getBox->SetisActiv(false);

		SAFE_RELEASE(getBox);
	}
}

void Commando::RockHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "RockHit")
	{
		RockGolenHitBox* getBox = (RockGolenHitBox*)Dest->GetCurObject();

		if (pState != PS_SKILL3 && isInfinity == false)
		{
			Hp -= getBox->GetAttack();

			Number* DamegaNumber = Object::CreateObject<Number>("DamegaNumber", m_Layer);
			DamegaNumber->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
			DamegaNumber->SetTexture("DamNumber", TEXT("object/BlueNumber.bmp"));
			DamegaNumber->SetNumberSize(19.0f, 24.0f);
			DamegaNumber->SetNumber(getBox->GetAttack());
			DamegaNumber->SetNumberViewSize(10.0f, 13.0f);
			DamegaNumber->SetMaxRange(50.0f, 100.0f);
			DamegaNumber->SetIsCameraMode(true);

			SAFE_RELEASE(DamegaNumber);
			isInfinity = true;

		}
		else if(pState == PS_SKILL3)
			SoundManager::Get()->Play("Miss");

		getBox->SetisActiv(false);

		SAFE_RELEASE(getBox);
	}
}

void Commando::ColocussKickHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "ColossusKickHitBox")
	{
		ColossusKickHitBox* getBox = (ColossusKickHitBox*)Dest->GetCurObject();

		if (pState != PS_SKILL3 && isInfinity == false)
		{
			Hp -= getBox->GetAttack();

			Number* DamegaNumber = Object::CreateObject<Number>("DamegaNumber", m_Layer);
			DamegaNumber->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
			DamegaNumber->SetTexture("DamNumber", TEXT("object/BlueNumber.bmp"));
			DamegaNumber->SetNumberSize(19.0f, 24.0f);
			DamegaNumber->SetNumber(getBox->GetAttack());
			DamegaNumber->SetNumberViewSize(10.0f, 13.0f);
			DamegaNumber->SetMaxRange(50.0f, 100.0f);
			DamegaNumber->SetIsCameraMode(true);

			SAFE_RELEASE(DamegaNumber);
			isInfinity = true;
		}
		else if(pState == PS_SKILL3)
			SoundManager::Get()->Play("Miss");

		getBox->SetisActiv(false);
		SAFE_RELEASE(getBox);
	}
}

void Commando::ColocussClapHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "ColossusClapHitBox")
	{
		ColossusClapHitBox* getBox = (ColossusClapHitBox*)Dest->GetCurObject();

		if (pState != PS_SKILL3 && isInfinity == false)
		{
			Hp -= getBox->GetAttack();

			Number* DamegaNumber = Object::CreateObject<Number>("DamegaNumber", m_Layer);
			DamegaNumber->SetPos(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
			DamegaNumber->SetTexture("DamNumber", TEXT("object/BlueNumber.bmp"));
			DamegaNumber->SetNumberSize(19.0f, 24.0f);
			DamegaNumber->SetNumber(getBox->GetAttack());
			DamegaNumber->SetNumberViewSize(10.0f, 13.0f);
			DamegaNumber->SetMaxRange(50.0f, 100.0f);
			DamegaNumber->SetIsCameraMode(true);

			SAFE_RELEASE(DamegaNumber);
			isInfinity = true;
		}
		else if(pState == PS_SKILL3)
			SoundManager::Get()->Play("Miss");

		getBox->SetisActiv(false);
		SAFE_RELEASE(getBox);
	}
}

void Commando::ItemHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "ItemBody")
	{
		if (KEYDown('A'))
		{
			ItemBase* getItem = (ItemBase*)Dest->GetCurObject();

			switch (getItem->GetItemKind())
			{
				case ItemBase::ITEM_KIND::ITEM_BOOSTER:
				{
					getItem->SetIsCameraMode(false);
					getItem->SetIsStop(true);
					//포지션을 업데이트에서 리스트돌려서..?

					list<ItemBase*>::iterator StartIter = myItemList.begin();
					list<ItemBase*>::iterator EndIter= myItemList.end();

					int Count = 0;
					for (; StartIter != EndIter; StartIter++)
					{
						Count++;
					}

					getItem->SetPos(Vector2((float)Count + 30.0f, Core::Get()->GetWinSizeVector2().y - 200.0f));
					myItemList.push_back(getItem);
				}
					break;
				case ItemBase::ITEM_KIND::ITEM_ALIENHEAD:
				{

				}
					break;
				case ItemBase::ITEM_KIND::ITEM_FIREMANBOOT:
					break;
				case ItemBase::ITEM_KIND::ITEM_FIRESHIELD:
					break;
				case ItemBase::ITEM_KIND::ITEM_KNIFE:
					break;
				case ItemBase::ITEM_KIND::ITEM_TASER:
					break;
				case ItemBase::ITEM_KIND::ITEM_TELESCOPE:
					break;
				case ItemBase::ITEM_KIND::ITEM_TOUGHTIME:
					break;
			}
		}
	}
}

void Commando::LineHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "MonsterBody")
	{
		HitSize = ((ColliderRect*)Dest)->GetSize();
		HitPos = Dest->GetPos();

		HitSizeList.push_back(HitSize);
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

		list<Vector2>::iterator StartSizeIter = HitSizeList.begin();
		list<Vector2>::iterator EndSizeIter = HitSizeList.end();

		for (;StartSizeIter != EndSizeIter; StartSizeIter++)
		{
			if (HitSize > *StartSizeIter)
				HitSize = *StartSizeIter;
		}
		isLineHit = true;
	}
}