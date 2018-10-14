#include "Coin.h"
#include "../Coll/ColliderRect.h"

Coin::Coin()
	:Target(NULL)
{
	m_ObjectType = OT_ITEM;
	SetTag("Coin");
}

Coin::Coin(const Coin & Value)
	:Object(Value)
{
	Target = Value.Target;
	this->Value = Value.Value;
	TimeVar = Value.TimeVar;
	FinishTime = Value.FinishTime;
	isFollow = false;
}

Coin::~Coin()
{
}

bool Coin::Init()
{
	Value = 0;
	TimeVar = 0.0f;
	isFollow = false;
	FinishTime = 2.0f;

	SetPivot(0.5f, 0.5f);
	SetMoveSpeed(500.0f);

	//中宜端持失
	ColliderRect* RC = AddCollider<ColliderRect>("CoinBody");
	RC->SetVirtualRect(m_Size);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Coin");
	SAFE_RELEASE(RC);

	return true;
}

int Coin::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int Coin::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	ColliderRect* myCollider = (ColliderRect*)GetCollider("CoinBody");
	myCollider->SetVirtualRect(m_Size);
	SAFE_RELEASE(myCollider);

	TimeVar += DeltaTime;

	if (TimeVar >= FinishTime)
	{
		isFollow = true;
		TimeVar = 0.0f;
	}

	if (isFollow == true && Target != NULL)
	{
		m_Angle = Math::GetDegree(m_Pos, Target->GetPos());
		MoveByAngle(DeltaTime);
	}

	return 0;
}

int Coin::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void Coin::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Coin::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

Coin * Coin::Clone()
{
	return new Coin(*this);
}

void Coin::SetTarget(Object * pTarget)
{
	if (Target != NULL)
		Target->AddRefCount();

	Target = pTarget;
}
