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
		SoundManager::Get()->Play("Stun");

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