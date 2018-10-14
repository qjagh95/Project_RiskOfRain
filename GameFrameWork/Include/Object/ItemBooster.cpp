#include "ItemBooster.h"
#include "../Coll/ColliderRect.h"
#include "../Scene/Layer.h"
#include "../Object/Commando.h"
#include "../Object/Bar.h"

ItemBooster::ItemBooster()
{
	ItemKind = ITEM_BOOSTER;
}

ItemBooster::ItemBooster(const ItemBooster & Value)
	:ItemBase(Value)
{
	SAFE_RELEASE(OilBar);
}

ItemBooster::~ItemBooster()
{
}

bool ItemBooster::Init()
{
	ItemBase::Init();
	GaugeTime = 3.0f;
	MaxTime = 3.0f;
	SetTexture("BoosterItem", TEXT("Item/JetPack.bmp"));

	OilBar = Object::CreateObject<Bar>("OilBar", m_Layer);
	OilBar->SetSize(Vector2(45.0f, 41.0f));
	OilBar->SetTexture("OilBar", TEXT("Effect/Booster.bmp"));
	OilBar->SetColorKey(RGB(255, 0, 255));
	OilBar->SetIsCameraMode(true);
	return true;

}

int ItemBooster::Input(float DeltaTime)
{
	ItemBase::Input(DeltaTime);

	return 0;
}

int ItemBooster::Update(float DeltaTime)
{
	ItemBase::Update(DeltaTime);

	return 0;
}

int ItemBooster::LateUpdate(float DeltaTime)
{
	ItemBase::LateUpdate(DeltaTime);
	return 0;
}

void ItemBooster::Collision(float DeltaTime)
{
	ItemBase::Collision(DeltaTime);
}

void ItemBooster::Render(HDC Hdc, float DeltaTime)
{
	ItemBase::Render(Hdc, DeltaTime);
}

ItemBooster * ItemBooster::Clone()
{
	return new ItemBooster(*this);
}

void ItemBooster::EffectUpdate(float DeltaTime)
{
	//점프일때만 들어온다.
	if (Commando::GetPlayerState() != PS_JUMPING)
		return;

	if (KEYPress(VK_SPACE))
	{
		GaugeTime -= DeltaTime;

		if (GaugeTime <= 0.0f)
		{
			GaugeTime = 0.0f;
			OilBar->SetisShow(false);
			return;
		}

		Target->SetPos(Target->GetPos().x, Target->GetPos().y - Target->GetMoveSpeed() * DeltaTime);

		Target->SetForce(0.0f);
		OilBar->SetBarInfo(0, (int)MaxTime, (int)GaugeTime, BD_DOWN);
		OilBar->SetPos(Target->GetPos().x + Target->GetSize().x , Target->GetPos().y);
		OilBar->SetisShow(true);
	}
	else
	{
		GaugeTime += DeltaTime;

		if(GaugeTime >= MaxTime)
			GaugeTime = MaxTime;

		OilBar->SetisShow(false);
	}
}
