#include "IssacEnemy1.h"
#include "../Coll/ColliderRect.h"

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
