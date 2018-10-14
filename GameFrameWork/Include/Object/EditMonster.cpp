#include "EditMonster.h"
#include "../Coll/ColliderRect.h"
#include "../Input.h"
#include "TileInfo.h"
#include "Tile.h"
#include "../StageManager.h"

EditMonster* EditMonster::EditSelect = NULL;
bool EditMonster::isSelect = false;

EditMonster::EditMonster()
{
	m_ObjectType = OT_EDITOBJECT;
	SetTag("EditMonster1");
}

EditMonster::EditMonster(const EditMonster & Value)
	:Object(Value)
{
}

EditMonster::~EditMonster()
{
	SAFE_RELEASE(RC);
}

bool EditMonster::Init()
{
	SetSize(100.0f, 100.0f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Yasuo", TEXT("Yasuo.bmp"));
	SetColorKey(RGB(255, 0, 255));

	//中宜端持失
	RC = AddCollider<ColliderRect>("EditMonsterBody");
	RC->SetVirtualRect(100.0f, 100.0f);
	RC->SetPivot(0.5f, 0.5f);
	RC->SetCollsionTypeName("EditMonster");
	RC->SetCallBack(this, &EditMonster::MouseHit, CS_COLDOING);

	return true;
}

int EditMonster::Input(float DeltaTime)
{
	Object::Input(DeltaTime);
	return 0;
}

int EditMonster::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int EditMonster::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);
	return 0;
}

void EditMonster::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void EditMonster::Render(HDC Hdc, float DeltaTime)
{
	Object::Render(Hdc, DeltaTime);
}

EditMonster * EditMonster::Clone()
{
	return new EditMonster(*this);
}

void EditMonster::MouseHit(Collider * Src, Collider * Dest, float DeltaTime)
{
	if(Dest->GetTag() =="MouseObject")
	{	
		if (KEYDOWN("LBotton"))
		{
			isSelect = true;

			EditSelect = this;
			Src->GetCurObject(); //AddRef()
		}

		if (KEYPRESS("LBotton"))
		{
			if (EditSelect != NULL)
			{
				Vector2 mPos = Input::Get()->GetMouseWorldPos();
				EditSelect->SetPos(mPos);
			}
		}

		if (KEYUP("LBotton"))
		{
			isSelect = false;
			SAFE_RELEASE(EditSelect);
		}

		if (KEYDOWN("RBotton"))
			SetisActiv(false);
	}
}

