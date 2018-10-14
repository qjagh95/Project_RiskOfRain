#include "Colossus.h"
#include "../Coll/ColliderRect.h"
#include "../Scene/Layer.h"
#include "../Object/Object.h"
#include "../Object/Tile.h"
#include "../StageManager.h"
#include "../Resource/Animation.h"
#include "../Scene/MainScene.h"
#include "../Object/AncientEffect.h"
#include "../Object/Bar.h"
#include "../Object/Number.h"
#include "../Object/ColossusKickHitBox.h"
#include "../Object/ColossusClapHitBox.h"
#include "../BossBarEdge.h"
#include "../Debug.h"
#include "../Sound/SoundManager.h"

Colossus::Colossus()
	:HpNumber(NULL), BossHpBar(NULL)
{
}

Colossus::Colossus(const Colossus & Value)
	:Monster(Value)
{
}

Colossus::~Colossus()
{
	SAFE_RELEASE(newEdge);
	SAFE_RELEASE(HpNumber);
	SAFE_RELEASE(BossHpBar);
}

bool Colossus::Init()
{
	Monster::Init();

	SetHp(1800);
	SetMaxHp(1800);

	newEdge = Object::CreateObject<BossBarEdge>("BarEdge", m_Layer);
	newEdge->SetPos(5.0f, 15.0f);

	BossHpBar = Object::CreateObject<Bar>("BossHpBar", m_Layer);
	BossHpBar->SetPos(12.0f, 22.0f);
	BossHpBar->SetSize(1770.0f, 28.0f);
	BossHpBar->SetBarInfo(0, GetMaxHp(), GetHp());
	BossHpBar->SetTexture("BossHpBar", TEXT("BossBar2.bmp"));
	BossHpBar->SetIsCameraMode(false);

	HpNumber = Object::CreateObject<Number>("BossHpNumber", m_Layer);
	HpNumber->SetPos(Core::Get()->GetWinSizeVector2().x / 2.0f, 22.0f);
	HpNumber->SetTexture("BossHpNumber", TEXT("object/TempNumber.bmp"));
	HpNumber->SetNumberSize(19.0f, 24.0f);
	HpNumber->SetNumber(GetHp());
	HpNumber->SetNumberViewSize(30.0f, 25.0f);
	HpNumber->SetIsCameraMode(false);

	KickDamege = 48;
	ClapDamege = 65;

	KickRange = 500;
	ClapRange = 300;

	SerchRange = 0.0f;

	SetSize(270.0f, 360.0f);
	SetPivot(0.5f, 0.5f);
	SetMoveSpeed(100.0f);
	SetMoneyCoinCount(30);
	SetExpCoinCount(30);
	SetBarIsShow(false);
	MainScene::SetStageOneBoss(true);

	int a = rand() % 2;
	if (a == 0)
	{
		Dir = "R";
		MoveDir = 1.0f;
	}
	else
	{
		Dir = "L";
		MoveDir = -1.0f;
	}

	AnimationName[CS_MOVE] = "Move";
	AnimationName[CS_CLAP] = "Clap";
	AnimationName[CS_KICK] = "Kick";

	AddAnimationClip("LMove", AT_ATLAS, AO_LOOP, 270.0f, 360.0f, 25, 1, 25, 1, 0, 0, 1.0f, "COLMOVE", TEXT("Enemy/Colossus_Left_Move.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_REVERS_LOOP, 270.0f, 360.0f, 25, 1, 25, 1, 24, 0, 1.0f, "CORMOVE", TEXT("Enemy/Colossus_Right_Move.bmp"));
	AddAnimationClip("LClap", AT_ATLAS, AO_LOOP_BOSS_BOUNCE, 530.0f, 350.0f, 21, 1, 21, 1, 0, 0, 1.0f, "COLCLAP", TEXT("Enemy/Colossus_Left_Attack.bmp"));
	AddAnimationClip("RClap", AT_ATLAS, AO_REVERS_LOOP_BOSS_BOUNCE, 530.0f, 350.0f, 21, 1, 21, 1, 20, 0, 1.0f, "CORCLAP", TEXT("Enemy/Colossus_Right_Attack.bmp"));
	AddAnimationClip("LKick", AT_ATLAS, AO_REVERS_LOOP_BOSS_BOUNCE, 312.0f, 360.0f, 21, 1, 21, 1, 20, 0, 1.5f, "COLKICK", TEXT("Enemy/Colossus_Left_Attack2.bmp"));
	AddAnimationClip("RKick", AT_ATLAS, AO_LOOP, 312.0f, 350.0f, 21, 1, 21, 1, 0, 0, 1.5f, "CORKICK", TEXT("Enemy/Colossus_Right_Attack2.bmp"));

	SelectState(AnimationName, CS_MOVE);

	return true;
}

int Colossus::Input(float DeltaTime)
{
	Monster::Input(DeltaTime);

	BossHpBar->SetBarInfo(0, GetMaxHp(), GetHp());
	HpNumber->SetNumber(GetHp());

	return 0;
}

int Colossus::Update(float DeltaTime)
{
	Monster::Update(DeltaTime);

	AnimationDirCheck(AnimationName, mState);

	if (Distance < ClapRange)
		SerchRange = ClapRange;
	else if (Distance < KickRange)
		SerchRange = KickRange;

	switch (mState)
	{
		case CS_MOVE:
			FS_MOVE(DeltaTime);
			break;
		case CS_CLAP:
			FS_CLAP(DeltaTime);
			break;
		case CS_KICK:
			FS_KICK(DeltaTime);
			break;
	}

	if (GetHp() <= 0)
	{
		SetHp(0);
		MainScene::SetStageOneBoss(false);
		MainScene::SetSommonMode(false);
		SoundManager::Get()->Stop("DNF");
		SoundManager::Get()->Play("BGM");
		newEdge->SetisActiv(false);
		HpNumber->SetisActiv(false);
	}

	return 0;
}

int Colossus::LateUpdate(float DeltaTime)
{
	Monster::LateUpdate(DeltaTime);

	PrevFrame = m_Animation->GetFrameX();
	AnimationDirCheck(AnimationName, mState);
	SerchRange = 0;

	return 0;
}

void Colossus::Collision(float DeltaTime)
{
	Monster::Collision(DeltaTime);
}

void Colossus::CollsionAfterUpdate(float DeltaTime)
{
	Monster::CollsionAfterUpdate(DeltaTime);
}

void Colossus::Render(HDC Hdc, float DeltaTime)
{
	Monster::Render(Hdc, DeltaTime);
}

Colossus * Colossus::Clone()
{
	return new Colossus(*this);
}

void Colossus::TileCollsionActive(float DeltaTime)
{
	Monster::TileCollsionActive(DeltaTime);
}

void Colossus::RangeCheck()
{
	if (SerchRange == ClapRange)
		SelectState(AnimationName, CS_CLAP);
	else if (SerchRange == KickRange)
		SelectState(AnimationName, CS_KICK);
}

void Colossus::FS_MOVE(float DeltaTime)
{
	Tile* CurTile = NULL;
	Tile* FootTile = NULL;
	Tile* NextTile = NULL;

	NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX() * MoveDir, m_Pos.y);
	CurTile = StageManager::Get()->GetTile(m_Pos.x, m_Pos.y - m_Size.GetHalfY());
	FootTile = StageManager::Get()->GetTile(m_Pos.x + (m_Size.GetHalfX() * MoveDir) + StageManager::Get()->GetTileSize().GetHalfX(), m_Pos.y + m_Size.GetHalfY() + StageManager::Get()->GetTileSize().GetHalfY());

	if (m_Pos.x >= 0 || m_Pos.x < StageManager::Get()->GetWidth())
	{
		if (FootTile->GetTileType() != TT_NOMAL)
			m_Pos.x += MoveSpeed * MoveDir * DeltaTime;
		else if (FootTile->GetTileType() == TT_NOMAL)
			MoveDir *= -1.0f;
		else
			DirCheck();

		if (NextTile->GetTileType() == TT_NOMOVE)
			MoveDir *= -1.0f;
	}

	if (CurTile->GetTileType() == TT_NOMOVE && FootTile->GetTileType() == TT_NOMAL)
		MoveDir *= -1.0f;

	SAFE_RELEASE(NextTile);
	SAFE_RELEASE(FootTile);
	SAFE_RELEASE(CurTile);

	RangeCheck();
}

void Colossus::FS_CLAP(float DeltaTime)
{
	if (PrevFrame == m_Animation->GetFrameX())
		return;

	if (MoveDir == 1.0f)
	{
		if (m_Animation->GetFrameX() == 10)
		{
			ColossusClapHitBox* newBox = Object::CreateObject<ColossusClapHitBox>("ColossusClapHitBox", m_Layer);
			newBox->SetPos(m_Pos.x, m_Pos.y);
			newBox->SetAttack(ClapDamege);

			SAFE_RELEASE(newBox);
		}
	}
	else
	{
		if (m_Animation->GetFrameX() == m_Animation->GetMaxCountX() - 10)
		{
			ColossusClapHitBox* newBox = Object::CreateObject<ColossusClapHitBox>("ColossusClapHitBox", m_Layer);
			newBox->SetPos(m_Pos.x, m_Pos.y);
			newBox->SetAttack(ClapDamege);

			SAFE_RELEASE(newBox);
		}
	}

	if (m_Animation->GetIsEnd() == true)
	{
		DirCheck();

		if (Distance < ClapRange)
			SelectState(AnimationName, CS_CLAP);
		else if (Distance < KickRange)
			SelectState(AnimationName, CS_KICK);
		else
			SelectState(AnimationName, CS_MOVE);
	}
}

void Colossus::FS_KICK(float DeltaTime)
{
	if (PrevFrame == m_Animation->GetFrameX())
		return;

	if (MoveDir == 1.0f)
	{
		if (m_Animation->GetFrameX() == 9)
		{
			Vector2 TempPos = Target->GetPos();
			Tile* TempTile = NULL;

			ColossusKickHitBox* newBox = Object::CreateObject<ColossusKickHitBox>("ColossusClapHitBox", m_Layer);
			while (true)
			{
				TempTile = StageManager::Get()->GetTile(TempPos);

				if (TempTile->GetTileType() == TT_NOMOVE)
				{
					newBox->SetPos(TempPos.x, TempPos.y);
					SAFE_RELEASE(TempTile);
					break;
				}
				else
					TempPos.y++;

				SAFE_RELEASE(TempTile);
			}
			newBox->SetAttack(KickDamege);
			SAFE_RELEASE(newBox);
			SAFE_RELEASE(TempTile);
		}
	}
	else
	{
		if (m_Animation->GetFrameX() == 9)
		{
			Vector2 TempPos = Target->GetPos();
			Tile* TempTile = NULL;

			ColossusKickHitBox* newBox = Object::CreateObject<ColossusKickHitBox>("ColossusClapHitBox", m_Layer);
			while (true)
			{
				TempTile = StageManager::Get()->GetTile(TempPos);

				if (TempTile->GetTileType() == TT_NOMOVE)
				{
					newBox->SetPos(TempPos.x, TempPos.y);
					SAFE_RELEASE(TempTile);
					break;
				}
				else
					TempPos.y++;

				SAFE_RELEASE(TempTile);
			}
			newBox->SetAttack(KickDamege);
			SAFE_RELEASE(newBox);
			SAFE_RELEASE(TempTile);
		}
	}

	if (m_Animation->GetIsEnd() == true)
	{
		DirCheck();

		if (Distance < ClapRange)
			SelectState(AnimationName, CS_CLAP);
		else if (Distance < KickRange)
			SelectState(AnimationName, CS_KICK);
		else
			SelectState(AnimationName, CS_MOVE);
	}
}
