#include "Rope.h"
#include "Object.h"

#include "Tile.h"
#include "TileInfo.h"

#include "../Camera.h"

#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/Animation.h"

#include "../Coll/ColliderRect.h"

#include "../Scene/Layer.h"

Rope::Rope()
{
	m_ObjectType = OT_ROPE;
	SetTag("RopeObject");
}

Rope::Rope(const Rope & Value)
	:Object(Value)
{
}

Rope::~Rope()
{
	SAFE_RELEASE(RC);
}

bool Rope::Init()
{
	SetPivot(0.5f, 0.0f);

	SetTexture("RopeObject", TEXT("object/Rope.bmp"));
	SetColorKey(RGB(255, 0, 255));

	//中宜端持失
	RC = AddCollider<ColliderRect>("RopeBody");
	RC->SetVirtualRect(m_Size);
	RC->SetPivot(0.5f, 0.0f);
	RC->SetCallBack(this, &Rope::PlayerCol, CS_COLDOING);
	RC->SetCollsionTypeName("Rope");

	return true;
}

int Rope::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int Rope::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	RC->SetVirtualRect(m_Size.x, m_Size.y);

	return 0;
}

int Rope::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void Rope::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void Rope::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

Rope * Rope::Clone()
{
	return new Rope(*this);
}

void Rope::PlayerCol(Collider * Src, Collider * Dest, float DeltaTime)
{
	if (Dest->GetTag() == "PlayerPoint")
	{
		int a = 0;
	}
}

