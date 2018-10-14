#pragma once
#include "Object.h"
class ItemBase : public Object
{
public:
	friend class Object;

	virtual bool Init();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC Hdc, float DeltaTime);
	virtual ItemBase* Clone();

protected:
	ItemBase();
	ItemBase(const ItemBase& Value);
	~ItemBase();
};

