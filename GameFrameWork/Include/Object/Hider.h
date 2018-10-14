#pragma once
#include "Object.h"
class Number;
class Layer;
class Hider : public Object
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	Hider* Clone() override;

	void SetHider(Layer* pLayer ,SKILL_TYPE eType, int dTime);
	int GetDelayTime() const { return DelayTime; }

private:
	Number* DelayTimeNumber;
	int DelayTime;

protected:
	Hider();
	Hider(const Hider& Value);
	~Hider();
};

