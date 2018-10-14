#include "IssacTear.h"
#include "../Coll/ColliderRect.h"
#include "../Object/Tile.h"
#include "../StageManager.h"

IssacTear::IssacTear()
{
	m_ObjectType = OT_BULLET;
	SetTag("Tear");
}

IssacTear::IssacTear(const IssacTear & Value)
	:Object(Value)
{
	MoveDir = Value.MoveDir;
	Attack = Value.Attack;
}

IssacTear::~IssacTear()
{
}

bool IssacTear::Init()
{
	MoveDir = 1.0f;
	Attack = 8;

	SetTexture("IssacTear", TEXT("Enemy/Tear.bmp"));
	SetColorKey(RGB(255, 0, 255));
	SetSize(13.0f, 13.0f);
	SetPivot(0.5f, 0.5f);
	SetGravity(true);

	ColliderRect* RC = AddCollider<ColliderRect>("TearBody");
	RC->SetVirtualRect(m_Size);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("Monster");

	SAFE_RELEASE(RC);

	return true;
}

int IssacTear::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int IssacTear::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	Tile* CurTile = StageManager::Get()->GetTile(m_Pos);

	if (CurTile->GetTileType() == TT_NOMOVE)
		SetisActiv(false);

	if (m_Pos.x <= 0.0f || m_Pos.x >= StageManager::Get()->GetWidth())
		SetisActiv(false);

	if (m_Pos.y <= 0.0f || m_Pos.y >= StageManager::Get()->GetHight())
		SetisActiv(false);

	m_Pos.x += MoveSpeed * MoveDir * DeltaTime;

	SAFE_RELEASE(CurTile);

	return 0;
}

int IssacTear::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void IssacTear::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void IssacTear::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

IssacTear * IssacTear::Clone()
{
	return new IssacTear(*this);
}
