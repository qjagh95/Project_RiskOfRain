#pragma once
#include "Object.h"
class Rope : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	Rope* Clone() override;

protected:
	Rope();
	Rope(const Rope& Value);
	~Rope();
};

