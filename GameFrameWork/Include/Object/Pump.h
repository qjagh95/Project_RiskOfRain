#pragma once
#include "Object.h"
class Pump : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	Pump* Clone() override;

	void PlayerColl(Collider* Src, Collider* Dest, float DeltaTime);

protected:
	Pump();
	Pump(const Pump& Value);
	~Pump();
};

