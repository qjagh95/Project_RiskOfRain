#include "Player.h"
#include "../stdafx.h"
#include "../Input.h"
#include "../Coll/ColliderRect.h"
#include "../Coll/ColliderCircle.h"
#include "../Coll/ColliderPixel.h"
#include "../Coll/CollsionManager.h"
#include "../Resource/Animation.h"
#include "../Scene/Layer.h"
#include "Bullet.h"
#include "TargetBullet.h"
#include "FollowBullet.h"
#include "../Camera.h"
#include "Effect.h"
#include "../Object/Tile.h"
#include "../Object/TileInfo.h"
#include "../Sound/SoundManager.h"
#include "../StageManager.h"

void Player::FS_Idle(float DeltaTime)
{
	if (KEYPRESS("Right"))
		SelectState(PLAYER_STATE::PS_MOVE);
	else if (KEYPRESS("Left"))
		SelectState(PLAYER_STATE::PS_MOVE);

	if (KEYDOWN("Jump"))
	{
		isJumping = true;
		SetForce(100.0f);
		SelectState(PLAYER_STATE::PS_JUMPING);
	}
}

void Player::FS_Move(float DeltaTime)
{
	PlayerMove(DeltaTime);

	if (KEYDOWN("Jump"))
	{
		isJumping = true;
		SetForce(100.0f);
		SelectState(PLAYER_STATE::PS_JUMPING);
	}

	if (KEYPRESS("Right") == false && KEYPRESS("Left") == false)
		SelectState(PLAYER_STATE::PS_IDLE);
}

void Player::FS_Jump(float DeltaTime)
{
	PlayerMove(DeltaTime);

	if(isJumping == false)
		SelectState(PLAYER_STATE::PS_IDLE);
}

void Player::FS_BaseAttack(float DeltaTime)
{

}

void Player::FS_Skill1(float DeltaTime)
{

}

void Player::FS_Skill2(float DeltaTime)
{

}

void Player::FS_Skill3(float DeltaTime)
{

}

void Player::FS_Skill4(float DeltaTime)
{

}

void Player::FS_Rope(float DeltaTime)
{

}
