#pragma once
#include "EditMonster.h"
class EditMonster6 : public EditMonster
{
public:
	friend class Object;

	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void Render(HDC Hdc, float DeltaTime) override;
	virtual EditMonster6* Clone() override;

protected:
	EditMonster6();
	EditMonster6(const EditMonster6& Value);
	~EditMonster6();
};

