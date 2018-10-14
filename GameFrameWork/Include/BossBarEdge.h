#pragma once
#include "Object\Object.h"
class BossBarEdge : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	BossBarEdge* Clone() override;

protected:
	BossBarEdge();
	BossBarEdge(const BossBarEdge& Value);
	~BossBarEdge();
};

