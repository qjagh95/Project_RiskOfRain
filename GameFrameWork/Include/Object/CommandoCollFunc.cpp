#include "Commando.h"
#include "Bullet.h"
#include "Effect.h"

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

		Effect* newEffect = (Effect*)Object::CreateCloneObject("BomeEffect", m_Layer);
		newEffect->SetPos(newBullet->GetPos());

		SAFE_RELEASE(newEffect);
		SAFE_RELEASE(newBullet);
	}
}
void Commando::RopeHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "RopeBody")
	{
		isRopeHiting = true;
		m_Pos.x = Dest->GetPos().x;
	}
}