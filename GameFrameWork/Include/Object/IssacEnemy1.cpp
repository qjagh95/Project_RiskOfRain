#include "IssacEnemy1.h"

IssacEnemy1::IssacEnemy1()
{
}

IssacEnemy1::IssacEnemy1(const IssacEnemy1 & Value)
	:Monster(Value)
{
}

IssacEnemy1::~IssacEnemy1()
{
}

bool IssacEnemy1::Init()
{
	Monster::Init();

	//SetSize(0.0f, 0.0f);
	Dir = "R";
	MoveDir = 1.0f;

	TraceRange = 600.0f;
	SetMoveSpeed(250.0f);

	AnimationName[IMS_MOVE] = "Move";
	AnimationName[IMS_TRACE] = "Move";
	AnimationName[IMS_ATTACK] = "Attack";

	//AddAnimationClip("")
	//AddAnimationClip("")
	//AddAnimationClip("")

	return true;
}

int IssacEnemy1::Input(float DeltaTime)
{
	Monster::Input(DeltaTime);

	return 0;
}

int IssacEnemy1::Update(float DeltaTime)
{
	Monster::Update(DeltaTime);

	switch (mState)
	{
		case IMS_MOVE:
			FS_MOVE(DeltaTime);
			break;
		case IMS_ATTACK:
			FS_ATTACK(DeltaTime);
			break;
		case IMS_TRACE:
			FS_TRACE(DeltaTime);
			break;
	}

	return 0;
}

int IssacEnemy1::LateUpdate(float DeltaTime)
{
	Monster::LateUpdate(DeltaTime);
	return 0;
}

void IssacEnemy1::Collision(float DeltaTime)
{
	Monster::Collision(DeltaTime);
}

void IssacEnemy1::Render(HDC Hdc, float DeltaTime)
{
	Monster::Render(Hdc, DeltaTime);
}

IssacEnemy1 * IssacEnemy1::Clone()
{
	return new IssacEnemy1(*this);
}

void IssacEnemy1::TileCollsionActive(float DeltaTime)
{
	Monster::TileCollsionActive(DeltaTime);
}

void IssacEnemy1::SelectState(ISSAC1_MONSTER_STATE mState)
{
	this->mState = mState;
	ChangeClip(Dir + AnimationName[mState]);
}

void IssacEnemy1::FS_MOVE(float DeltaTime)
{

}
void IssacEnemy1::FS_TRACE(float DeltaTime)
{

}
void IssacEnemy1::FS_ATTACK(float DeltaTime)
{

}