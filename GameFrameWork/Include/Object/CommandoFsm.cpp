#include "Commando.h"
#include "Bullet.h"
#include "TargetBullet.h"
#include "FollowBullet.h"
#include "Effect.h"

#include "../stdafx.h"
#include "../Input.h"
#include "../Camera.h"

#include "../Scene/Layer.h"
#include "../Scene/Scene.h"
#include "../Object/Tile.h"
#include "../Object/TileInfo.h"

#include "../Object/Hider.h"

#include "../Coll/ColliderRect.h"
#include "../Coll/ColliderCircle.h"
#include "../Resource/Animation.h"

#include "../Sound/SoundManager.h"
#include "../StageManager.h"

void Commando::FS_Idle(float DeltaTime)
{
	if (KEYPRESS("Right"))
		SelectState(PLAYER_STATE::PS_MOVE);
	else if (KEYPRESS("Left"))
		SelectState(PLAYER_STATE::PS_MOVE);

	if (KEYDOWN("Jump"))
	{
		isJumping = true;
		SetForce(600.0f);
		SelectState(PLAYER_STATE::PS_JUMPING);
	}

	SkillState();
}

void Commando::FS_Move(float DeltaTime)
{
	if (KEYDOWN("Jump"))
	{
		isJumping = true;
		SetForce(600.0f); 
		SelectState(PLAYER_STATE::PS_JUMPING);
	}

	PlayerMove(DeltaTime);
	SkillState();

	if (KEYPRESS("Right") == false && KEYPRESS("Left") == false)
		SelectState(PLAYER_STATE::PS_IDLE);
}

void Commando::FS_Jump(float DeltaTime)
{
	PlayerMove(DeltaTime);

	if (isJumping == false)
	{
		SelectState(PLAYER_STATE::PS_IDLE);
		SetForce(0.0f);
		ClearGravityTime();
	}
}

void Commando::FS_Skill1(float DeltaTime)
{

	if (m_Animation->GetIsEnd() == true)
	{
		SelectState(PLAYER_STATE::PS_IDLE);
	}
}

void Commando::FS_Skill2(float DeltaTime)
{

	if (m_Animation->GetIsEnd() == true)
	{
		SelectState(PLAYER_STATE::PS_IDLE);
	}
}

void Commando::FS_Skill3(float DeltaTime)
{
	if (m_Animation->GetIsEnd() == true)
	{
		SelectState(PLAYER_STATE::PS_IDLE);
	}
}

void Commando::FS_Skill4(float DeltaTime)
{
	if (m_Animation->GetIsEnd() == true)
	{
		SelectState(PLAYER_STATE::PS_IDLE);
	}
}

void Commando::FS_Rope(float DeltaTime)
{

}
