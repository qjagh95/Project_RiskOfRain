#pragma once
#include "Object.h"
class Shield : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	Shield* Clone() override;

	void Defence(Collider* Src, Collider* Dest, float DeltaTime);

protected:
	Shield();
	Shield(const Shield& Value);
	~Shield();
};

