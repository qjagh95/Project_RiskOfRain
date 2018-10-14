#pragma once
#include "ItemBase.h"
class Bar;
class ItemBooster : public ItemBase
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	ItemBooster* Clone() override;
	void EffectUpdate(float DeltaTime) override;

private:
	float GaugeTime;
	float MaxTime;
	float Size;
	float MaxSize;

	bool isUp;
	Bar* OilBar;

protected:
	ItemBooster();
	ItemBooster(const ItemBooster& Value);
	~ItemBooster();
};

