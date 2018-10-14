#pragma once
#include "Coin.h"
class ExpCoin : public Coin
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	ExpCoin* Clone() override;

protected:
	ExpCoin();
	ExpCoin(const ExpCoin& Value);
	~ExpCoin();
};

