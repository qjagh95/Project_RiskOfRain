#pragma once
#include "EditMonster.h"
class EditMonster2 : public EditMonster
{
public:
	friend class Object;

	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void Render(HDC Hdc, float DeltaTime) override;
	virtual EditMonster2* Clone() override;

protected:
	EditMonster2();
	EditMonster2(const EditMonster2& Value);
	~EditMonster2();
};
