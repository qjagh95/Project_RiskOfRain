#include "Shield.h"
#include "../Coll/ColliderRect.h"
#include "Bullet.h"
#include "../Camera.h"

Shield::Shield()
{
	m_ObjectType = OT_SHIELD;
	SetTag("Shield");
}

Shield::Shield(const Shield & Value)
	:Object(Value)
{
}

Shield::~Shield()
{
}

bool Shield::Init()
{
	SetSize(50.0f, 200.0f);
	SetPivot(0.5f, 0.5f);
	SetMoveSpeed(50.0f);

	//中宜端持失
	ColliderRect* RC = AddCollider<ColliderRect>("ShieldBody");
	RC->SetVirtualRect(50.0f, 200.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCallBack<Shield>(this, &Shield::Defence, CS_COLFIRST);
	RC->SetCollsionTypeName("Shield");
	SAFE_RELEASE(RC);

	return true;
}

int Shield::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int Shield::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	MoveByAngle(DeltaTime);

	return 0;
}

int Shield::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void Shield::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Shield::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);

	Vector2 LeftTop = m_Pos - (m_Size * m_Pivot);
	Vector2 CenterPos = LeftTop - Camera::Get()->GetPos();

	Rectangle(Hdc, (int)CenterPos.x, (int)CenterPos.y, (int)(CenterPos.x + m_Size.x), (int)(CenterPos.y + m_Size.y));
}

Shield * Shield::Clone()
{
	return new Shield(*this);
}

void Shield::Defence(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "BulletBody")
	{
		Bullet*	newBullet = (Bullet*)Dest->GetCurObject();

		newBullet->SetAngle(180.0f - newBullet->GetAngle());

		SAFE_RELEASE(newBullet);
	}
}
