#include "AncientWisp.h"
#include "../Coll/ColliderRect.h"

#include "../Object/Object.h"
#include "../Object/Tile.h"
#include "../StageManager.h"
#include "../Resource/Animation.h"

#include "../Object/AncientEffect.h"

AncientWisp::AncientWisp()
{
}

AncientWisp::AncientWisp(const AncientWisp & Value)
	:Monster(Value)
{
}

AncientWisp::~AncientWisp()
{
}

bool AncientWisp::Init()
{
	Monster::Init();
	AttackTime = 0.0f;
	AttackRange = 300.0f;
	Attack = 18;

	SetSize(150.0f, 305.0f);
	SetPivot(0.5f, 0.5f);
	SetMoveSpeed(50.0f);
	SetMoneyCoinCount(15);
	SetExpCoinCount(16);

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

	SetHp(500);
	SetMaxHp(500);

	AnimationName[AS_MOVE] = "Move";
	AnimationName[AS_ATTACK] = "Attack";

	AddAnimationClip("LMove", AT_ATLAS, AO_LOOP, 150.0f, 305.0f, 5, 1, 5, 1, 0, 0, 0.5f, "ACLMove", TEXT("Enemy/AncientWisp_Left_Move.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_LOOP, 150.0f, 305.0f ,5 ,1, 5, 1, 0, 0, 0.5f, "ACRMove", TEXT("Enemy/AncientWisp_Right_Move.bmp"));
	AddAnimationClip("LAttack", AT_ATLAS, AO_REVERS_LOOP, 150.0f, 305.0f, 5, 1, 5, 1, 4, 0, 1.0f, "ACLAttack", TEXT("Enemy/AncientWisp_Left_Attack.bmp"));
	AddAnimationClip("RAttack", AT_ATLAS, AO_LOOP, 150.0f, 305.0f, 5, 1, 5, 1, 0, 0, 1.0f, "ACRAttack", TEXT("Enemy/AncientWisp_Right_Attack.bmp"));

	SelectState(AnimationName, AS_MOVE);

	return true;
}

int AncientWisp::Input(float DeltaTime)
{
	Monster::Input(DeltaTime);

	return 0;
}

int AncientWisp::Update(float DeltaTime)
{
	Monster::Update(DeltaTime);

	AnimationDirCheck(AnimationName, mState);

	switch (mState)
	{
		case AS_MOVE:
			FS_MOVE(DeltaTime);
			break;
		case AS_ATTACK:
			FS_ATTACK(DeltaTime);
			break;
	}

	if(isAttack == true)
	{
		AttackTime += DeltaTime;

		if (AttackTime >= 1.0f)
		{
			isAttack = false;
			AttackTime = 0.0f;
		}
	}

	return 0;
}

int AncientWisp::LateUpdate(float DeltaTime)
{
	Monster::LateUpdate(DeltaTime);

	PrevFrame = m_Animation->GetFrameX();

	return 0;
}

void AncientWisp::Collision(float DeltaTime)
{
	Monster::Collision(DeltaTime);
}

void AncientWisp::CollsionAfterUpdate(float DeltaTime)
{
	Monster::CollsionAfterUpdate(DeltaTime);
}

void AncientWisp::Render(HDC Hdc, float DeltaTime)
{
	Monster::Render(Hdc, DeltaTime);
}

AncientWisp * AncientWisp::Clone()
{
	return new AncientWisp(*this);
}

void AncientWisp::TileCollsionActive(float DeltaTime)
{
	Monster::TileCollsionActive(DeltaTime);
}

void AncientWisp::RangeCheck()
{
	if (Distance < AttackRange)
	{
		SelectState(AnimationName, AS_ATTACK);
		isAttack = true;
	}
}

void AncientWisp::FS_MOVE(float DeltaTime)
{
	Tile* NextTile = NULL;

	NextTile = StageManager::Get()->GetTile(m_Pos.x + m_Size.GetHalfX() * MoveDir, m_Pos.y + m_Size.GetHalfY() - StageManager::Get()->GetTileSize().y);

	if (m_Pos.x >= 0 || m_Pos.x < StageManager::Get()->GetWidth())
		m_Pos.x += MoveSpeed * MoveDir * DeltaTime;

	if (NextTile->GetTileType() == TT_NOMOVE)
		MoveDir *= -1.0f;

	SAFE_RELEASE(NextTile);

	RangeCheck();
}

void AncientWisp::FS_ATTACK(float DeltaTime)
{
	DirCheck();

	if (m_Animation->GetFrameX() == PrevFrame)
		return;

	if ((MoveDir == 1.0f && m_Animation->GetFrameX() == 4) || (MoveDir == -1.0f && m_Animation->GetFrameX() == 1))
	{
		AncientEffect* newEffect = (AncientEffect*)Object::CreateCloneObject("AncientEffect", m_Layer);
		newEffect->SetSize(m_Size);
		newEffect->SetPos(Target->GetPos().x, Target->GetPos().y + Target->GetSize().y + 10.0f);
		newEffect->SetAttack(Attack);

		SAFE_RELEASE(newEffect);
	}

	if (m_Animation->GetIsEnd() == true)
		SelectState(AnimationName, AS_MOVE);
}