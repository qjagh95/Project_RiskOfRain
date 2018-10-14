#pragma once
#include "Object.h"
class Charactor : public Object
{
public:
	Charactor();
	Charactor(const Charactor& Value) : Object(Value) { MoveSpeed = Value.MoveSpeed; }
	virtual ~Charactor();

	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void CollsionAfterUpdate(float DeltaTime) override;
	virtual void Render(HDC hDC, float DeltaTime) override;
	virtual Charactor* Clone() = 0;

	virtual void TileCollsionActive(float DeltaTime) {};
};

