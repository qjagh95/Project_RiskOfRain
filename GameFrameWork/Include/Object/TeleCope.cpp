#include "TeleCope.h"
#include "../Coll/ColliderRect.h"
#include "../Scene/Layer.h"
#include "../Object/Commando.h"
#include "../Debug.h"

TeleCope::TeleCope()
{
	ItemKind = ITEM_TELESCOPE;
}

TeleCope::TeleCope(const TeleCope & Value)
	:ItemBase(Value)
{
}

TeleCope::~TeleCope()
{
}

bool TeleCope::Init()
{
	ItemBase::Init();
	return true;
}

int TeleCope::Input(float DeltaTime)
{
	ItemBase::Input(DeltaTime);

	return 0;
}

int TeleCope::Update(float DeltaTime)
{
	ItemBase::Update(DeltaTime);

	return 0;
}

int TeleCope::LateUpdate(float DeltaTime)
{
	ItemBase::LateUpdate(DeltaTime);
	return 0;
}

void TeleCope::Collision(float DeltaTime)
{
	ItemBase::Collision(DeltaTime);
}

void TeleCope::Render(HDC Hdc, float DeltaTime)
{
	ItemBase::Render(Hdc, DeltaTime);
}

TeleCope * TeleCope::Clone()
{
	return new TeleCope(*this);
}

void TeleCope::EffectUpdate(float DeltaTime)
{
}
