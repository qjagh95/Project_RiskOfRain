#include "AncientWisp.h"



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

	SetSize(150.0f, 305.0f);
	SetPivot(0.5f, 0.5f);

	Dir = "R";

	AnimationName[AS_MOVE] = "Move";
	AnimationName[AS_ATTACK] = "Attack";

	AddAnimationClip("LMove", AT_ATLAS, AO_LOOP, 150.0f, 305.0f, 5, 1, 5, 1, 0, 0, 0.5f, "LMove", TEXT("Enemy/AncientWisp_Left_Move.bmp"));
	AddAnimationClip("RMove", AT_ATLAS, AO_LOOP, 150.0f, 305.0f ,5 ,1, 5, 1, 0, 0, 0.5f, "RMove", TEXT("Enemy/AncientWisp_Right_Move.bmp"));
	AddAnimationClip("LAttack", AT_ATLAS, AO_LOOP, 150.0f, 305.0f, 5, 1, 5, 1, 0, 0, 0.5f, "LAttack", TEXT("Enemy/AncientWisp_Left_Attack.bmp"));
	AddAnimationClip("RAttack", AT_ATLAS, AO_LOOP, 150.0f, 305.0f, 5, 1, 5, 1, 0, 0, 0.5f, "RAttack", TEXT("Enemy/AncientWisp_Right_Attack.bmp"));

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
	return 0;
}

int AncientWisp::LateUpdate(float DeltaTime)
{
	Monster::LateUpdate(DeltaTime);

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
}

void AncientWisp::SelectState(ANCIENTWISP_STATE mState)
{
	PrevState = mState;
	this->mState = mState;

}

void AncientWisp::FS_IDLE(float DeltaTime)
{
}

void AncientWisp::FS_MOVE(float DeltaTime)
{
}

void AncientWisp::FS_TRACE(float DeltaTime)
{
}

void AncientWisp::FS_ATTACK(float DeltaTime)
{
}
