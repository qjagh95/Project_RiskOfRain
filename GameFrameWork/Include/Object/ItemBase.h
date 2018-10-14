#pragma once
#include "Object.h"
class ColliderRect;
class Object;
class ItemBase : public Object
{
public:
	enum ITEM_KIND
	{
		ITEM_NONE,
		ITEM_BOOSTER,
		ITEM_KNIFE,
		ITEM_TELESCOPE,
		ITEM_TASER,
		ITEM_TOUGHTIME,
		ITEM_FIRESHIELD,
		ITEM_FIREMANBOOT,
		ITEM_ALIENHEAD,
		ITEM_MAX,
	};

public:
	friend class Object;

	virtual bool Init();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC Hdc, float DeltaTime);
	virtual ItemBase* Clone();

	virtual void EffectUpdate(float DeltaTime) {}

	void SetItemCount(int Value) { ItemCount = Value; }
	int GetItemCount() const { return ItemCount; }
	ITEM_KIND GetItemKind() const { return ItemKind; }
	void SetIsStop(bool Value) { isStop = Value; }
	void SetTempPos(Vector2 Value) { TempPos = Value; }

protected:
	ColliderRect* RC;
	ITEM_KIND ItemKind;

	int ItemCount;
	bool isNumberShow;
	bool isStop;
	Object* Target;

private:
	bool isUp;
	Vector2 TempPos;

protected:
	ItemBase();
	ItemBase(const ItemBase& Value);
	~ItemBase();
};

