#include "ShotGunBullet.h"
#include "../Coll/ColliderRect.h"
#include "SubBullet.h"
#include "../Math.h"

ShotGunBullet::ShotGunBullet()
{
	m_ObjectType = OT_BULLET;
	SetTag("ShowGunBullet");
}

ShotGunBullet::ShotGunBullet(const ShotGunBullet & Value)
	:Object(Value)
{
	DeleteDistance = Value.DeleteDistance;
}

ShotGunBullet::~ShotGunBullet()
{
}

bool ShotGunBullet::Init()
{
	SetSize(50.0f, 50.0f);
	SetPivot(0.5f, 0.5f);
	SetDeleteDistance(300.0f);
	SetMoveSpeed(200.0f);

	SetTexture("Bullet", TEXT("Pistol.bmp"));
	SetColorKey(RGB(0, 248, 0));

	//中宜端持失
	ColliderRect* RC = AddCollider<ColliderRect>("ShotGunBulletBody");
	RC->SetVirtualRect(50.0f, 50.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("ShotGunBullet");

	SAFE_RELEASE(RC);

	return true;
}

int ShotGunBullet::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int ShotGunBullet::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	DeleteDistance -= MoveSpeed * DeltaTime;
	MoveByAngle(DeltaTime);

	if (DeleteDistance <= 0.0f)
	{
		int RandNum = Math::RandomRange(20, 30);

		for (int i = 0; i < RandNum; i++)
		{
			float RandAngle = (float)(Math::RandomRange(270, 90));

			SubBullet* sBullet = (SubBullet*)Object::CreateCloneObject("SubBullet", m_Layer);
			sBullet->SetPos(m_Pos);
			sBullet->SetAngle(RandAngle);

			SAFE_RELEASE(sBullet);
		}

		SetisActiv(false);
	}

	return 0;
}

int ShotGunBullet::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void ShotGunBullet::Collision(float DeltaTime)
{

	Object::Collision(DeltaTime);
}

void ShotGunBullet::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

ShotGunBullet * ShotGunBullet::Clone()
{
	return new ShotGunBullet(*this);
}
