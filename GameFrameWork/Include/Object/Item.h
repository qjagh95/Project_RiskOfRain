#pragma once
#include "Object.h"
class Item : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	Item* Clone() override;

	void SetIsRush(bool Value) { isRush = Value; }

	void SetTarget(Object* Value)
	{
		SAFE_RELEASE(Target);

		if (Value != NULL)
			Value->AddRefCount();

		Target = Value;
	}

protected:
	Item();
	Item(const Item& Value);
	~Item();

private:
	Object* Target;
	bool isRush;
};

