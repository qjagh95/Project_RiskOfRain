#pragma once
#include "EditMonster.h"
class EditMonster3 : public EditMonster
{
public:
	friend class Object;

	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void Render(HDC Hdc, float DeltaTime) override;
	virtual EditMonster3* Clone() override;

protected:
	EditMonster3();
	EditMonster3(const EditMonster3& Value);
	~EditMonster3();
};

