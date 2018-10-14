#include "ItemBooster.h"
#include "../Coll/ColliderRect.h"
#include "../Scene/Layer.h"
#include "../Object/Commando.h"
#include "../Object/Bar.h"
#include "../Debug.h"

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
	GaugeTime = 1.0f;
	MaxTime = 1.0f;
	MaxSize = 41.0f;
	Size = 41.0f;

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
	if (Commando::GetIsBooster() == true)
	{
		if (KEYPress(VK_SPACE))
		{
			if (GaugeTime <= 0.0f)
				return;

			isUp = true;

			GaugeTime -= DeltaTime;
			Size -= (41.0f * DeltaTime);

			if (GaugeTime <= 0.0f)
			{
				GaugeTime = 0.0f;
				Size = 0.0f;

				OilBar->SetisShow(false);
				return;
			}
			else
				OilBar->SetisShow(true);

			Target->SetForce(0.0f);
			Target->SetGravity(false);
			Target->SetMoveUpPos(-300.0f * DeltaTime);
		}
	}
	if(Commando::GetPlayerState() > 0)
	{
		if (KEYUp(VK_SPACE))
			isUp = false;
	}

	if (isUp == false)
	{
		GaugeTime += DeltaTime;
		Size += 41.0f * DeltaTime;

		if (GaugeTime >= MaxTime * ItemCount)
		{
			GaugeTime = MaxTime * ItemCount;
			Size = MaxSize * ItemCount;
			OilBar->SetisShow(false);
			return;
		}
		else
			OilBar->SetisShow(true);
	}

	OilBar->SetBarInfo(0, (int)MaxSize * ItemCount, (int)Size, BD_DOWN);
	OilBar->SetPos(Target->GetPos().x + Target->GetSize().GetHalfX(), Target->GetPos().y + 10.0f);
}
