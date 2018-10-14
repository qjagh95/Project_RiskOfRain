#include "Commando.h"
#include "BaseAttackBullet.h"
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

#include "../Object/BaseAttackBullet.h"
#include "../Object/LaserBullet.h"
#include "../Object/BaseEffect.h"
#include "../Object/LaserEffect.h"

#include "../Debug.h"

void Commando::FS_Idle(float DeltaTime)
{
	if (KEYPRESS("Right"))
		SelectState(PLAYER_STATE::PS_MOVE);
	else if (KEYPRESS("Left"))
		SelectState(PLAYER_STATE::PS_MOVE);

	if (KEYDOWN("Jump"))
	{
		isJumping = true;

		m_Pos.y--;

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

		m_Pos.y--;

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

	Tile* CurTile = StageManager::Get()->GetTile(m_Pos);
	Tile* NextTile = StageManager::Get()->GetTile(m_TempMove.x, m_TempMove.y);

	if (isJumping == false)
	{
		SelectState(PLAYER_STATE::PS_IDLE);
		SetForce(0.0f);
	}

	if (NextTile->GetTileType() == TT_NOMOVE)
	{
		SelectState(PLAYER_STATE::PS_IDLE);
		SetForce(0.0f);
	}

	SAFE_RELEASE(CurTile);
	SAFE_RELEASE(NextTile);
}

void Commando::FS_Skill1(float DeltaTime)
{
	if (m_Animation->GetFrameX() == 1 || m_Animation->GetFrameX() == 3)
	{
		//프레임 중복으로 들어오기때문에 이전프레임 변수를 만들어서 이전프레임과 같다면 return;
		if (PrevFrame == m_Animation->GetFrameX())
			return;

		BaseAttackBullet* newBullet = (BaseAttackBullet*)Object::CreateCloneObject("BaseAttackBullet", m_Layer);
		newBullet->SetDir(MoveDir);
		newBullet->SetAttack(AttackDamege);
		newBullet->SetPos(Vector2(m_Pos.x + (m_Size.GetHalfX() * MoveDir), m_Pos.y));

		const list<class Collider*>* pCollList = newBullet->GetColliderList();

		list<Collider*>::const_iterator	StartIter;
		list<Collider*>::const_iterator	EndIter = pCollList->end();

		for (StartIter = pCollList->begin(); StartIter != EndIter; ++StartIter)
			(*StartIter)->SetCollsionTypeName("Commando");

		SAFE_RELEASE(newBullet);
		TimeVar = 0.0f;
	}

	if (m_Animation->GetIsEnd() == true)
	{
		SelectState(PLAYER_STATE::PS_IDLE);
		TimeVar = 0.0f;
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
	m_Pos.x += BASESPEED * MoveDir * DeltaTime;

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
	SetForce(0.0f);
	//x좌표 고정
	m_Pos.x = RopePos.x;

	bool Check1 = false;
	bool Check2 = false;

	Vector2 SerchPos;
	SerchPos.x = m_Pos.x;
	SerchPos.y = m_Pos.y - m_Size.GetHalfY() - StageManager::Get()->GetTileSize().y;

	Tile* CurTile = StageManager::Get()->GetTile(m_Pos);
	Tile* CurTile2 = StageManager::Get()->GetTile(SerchPos);
	
	if (CurTile->GetTileType() == TT_NOMOVE)
		Check1 = true;
	
	if (CurTile2->GetTileType() == TT_NOMOVE)
		Check2 = true;

	if (KEYPRESS("Up"))
	{
		if (Check1 == true && Check2 == true )
			return;

		ChangeClip("RopeUp");
		m_Pos.y -= 200.0f * DeltaTime;
	}
	else if (KEYPRESS("Down"))
	{
		ChangeClip("RopeUp");
		m_Pos.y += 200.0f * DeltaTime;
	}
	else
		ChangeClip("RopeHold");

	if (isRopeHiting == false)
		SelectState(PLAYER_STATE::PS_IDLE);

	if (KEYDOWN("RopeLeft") && CurTile->GetTileType() != TT_NOMOVE)
	{
		isJumping = true;
		SetForce(100.0f);
		SelectState(PLAYER_STATE::PS_JUMPING);
	}
	else if (KEYDOWN("RopeRight") && CurTile->GetTileType() != TT_NOMOVE)
	{
		isJumping = true;
		SetForce(100.0f);

		SelectState(PLAYER_STATE::PS_JUMPING);
	}

	SAFE_RELEASE(CurTile);
	SAFE_RELEASE(CurTile2);
}
