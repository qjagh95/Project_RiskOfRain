#pragma once
#include "Object.h"
class Number;
class ItemBox : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	ItemBox* Clone() override;

protected:
	ItemBox();
	ItemBox(const ItemBox& Value);
	~ItemBox();

private:
	int Price;
	Number* PriceNumber;

};

