#include "JellyFish.h"
#include "../Coll/ColliderRect.h"

#include "../Scene/Layer.h"

#include "../Object/Object.h"
#include "../Object/Tile.h"
#include "../StageManager.h"
#include "../Resource/Animation.h"

#include "../Object/AncientEffect.h"

#include "../Object/JellyFishHitBox.h"

JellyFish::JellyFish()
{
}

JellyFish::JellyFish(const JellyFish & Value)
	:Monster(Value)
{
}

JellyFish::~JellyFish()
{
}

bool JellyFish::Init()
{
	Monster::Init();
	AttackDelay = 5.0f;
	AttackRange = 50.0f;
	Attack = 10;
	TraceRange = 800.0f;
	SetGravity(false);
	ChangeTime = 0.0f;

	RC->SetCollsionTypeName("JellyBody");

	Dir = "";

	SetMoveSpeed(150.0f);
	SetHp(150);
	SetMaxHp(150);

	SetSize(30.0f, 30.0f);

	AnimationName[JS_MOVE] = "Move";
	AnimationName[JS_TRACE] = "Move";
	AnimationName[JS_ATTACK] = "Attack";

	AddAnimationClip("Move", AT_ATLAS, AO_LOOP, 30.0f, 30.0f, 4, 1, 4, 1, 0, 0, 0.5f, "JellyMove", TEXT("Enemy/JellyMove.bmp"));
	AddAnimationClip("Attack", AT_ATLAS, AO_LOOP, 33.0f, 32.0f, 2, 1, 2, 1, 0, 0, 0.8f, "JellyAttack", TEXT("Enemy/JellyAttack.bmp"));

	SelectState(JS_MOVE);

	float RandDegree = (float)Math::RandomRange(0, 360);
	m_Angle = RandDegree;

	return true;
}

int JellyFish::Input(float DeltaTime)
{
	Monster::Input(DeltaTime);
	SetForce(0.0f);

	return 0;
}

int JellyFish::Update(float DeltaTime)
{
	Monster::Update(DeltaTime);

	if(m_Pos.x + m_Size.GetHalfX() >= StageManager::Get()->GetWidth() || m_Pos.x - m_Size.GetHalfX() <= 0.0f )
		m_Angle = 180.0f - m_Angle;
	else if(m_Pos.y + m_Size.GetHalfY() >= 2400.0f || m_Pos.y - m_Size.GetHalfY() <= 0.0f)
		m_Angle = 360.0f - m_Angle;

	switch (mState)
	{
		case JS_MOVE:
			FS_MOVE(DeltaTime);
			break;
		case JS_TRACE:
			FS_TRACE(DeltaTime);
			break;
		case JS_ATTACK:
			FS_ATTACK(DeltaTime);
			break;
	}

	if (isAttack == true)
	{
		AttackDelay -= DeltaTime;

		if (AttackDelay <= 0.0f)
		{
			isAttack = false;
			AttackDelay = 5.0f;
		}
	}

	return 0;
}

int JellyFish::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	PrevFrame = m_Animation->GetFrameX();

	return 0;
}

void JellyFish::Collision(float DeltaTime)
{
	Monster::Collision(DeltaTime);
}

void JellyFish::CollsionAfterUpdate(float DeltaTime)
{
	Monster::CollsionAfterUpdate(DeltaTime);
}

void JellyFish::Render(HDC Hdc, float DeltaTime)
{
	Monster::Render(Hdc, DeltaTime);
}

JellyFish * JellyFish::Clone()
{
	return new JellyFish(*this);
}

void JellyFish::TileCollsionActive(float DeltaTime)
{
	Monster::TileCollsionActive(DeltaTime);
}

void JellyFish::RangeCheck()
{
	if (Distance < TraceRange)
		SelectState(JS_TRACE);
}

void JellyFish::SelectState(JELLYFISH_STATE mState)
{
	PrevState = mState;
	this->mState = mState;

	ChangeClip(AnimationName[this->mState]);
}

void JellyFish::FS_MOVE(float DeltaTime)
{
	ChangeTime += DeltaTime;

	SetMoveSpeed(150.0f);

	if (ChangeTime >= 2.0f)
	{
		m_Angle = (float)Math::RandomRange(0, 360);
		ChangeTime = 0.0f;
	}

	MoveByAngle(DeltaTime);
	RangeCheck();
}

void JellyFish::FS_TRACE(float DeltaTime)
{
	m_Angle = PlayerDgree;
	SetMoveSpeed(200.0f);
	MoveByAngle(DeltaTime);

	if (Distance > TraceRange)
		SelectState(JS_MOVE);

	if (Distance < AttackRange)
	{
		SelectState(JS_ATTACK);
		isAttack = true;
	}
}

void JellyFish::FS_ATTACK(float DeltaTime)
{	
	SetMoveSpeed(150.0f);
	MoveByAngle(DeltaTime);

	if (isAttack == false)
	{
		m_Angle = (float)Math::RandomRange(0, 360);
		SelectState(JS_MOVE);
	}

	if (m_Animation->GetFrameX() == PrevFrame)
		return;

	if (m_Animation->GetIsEnd() == true)
	{
		JellyFishHitBox* newHitBox = Object::CreateObject<JellyFishHitBox>("JellyHitBox", m_Layer);
		newHitBox->SetPos(m_Pos);
		newHitBox->SetAttack(Attack);
		SAFE_RELEASE(newHitBox);

		SelectState(JS_MOVE);
	}
}
