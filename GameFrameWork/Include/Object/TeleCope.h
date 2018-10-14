#pragma once
#include "ItemBase.h"
class TeleCope : public ItemBase
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	TeleCope* Clone() override;
	void EffectUpdate(float DeltaTime) override;

protected:
	TeleCope();
	TeleCope(const TeleCope& Value);
	~TeleCope();
};

