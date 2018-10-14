#pragma once
#include "EditMonster.h"
class EditMonster4 : public EditMonster
{
public:
	friend class Object;

	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void Render(HDC Hdc, float DeltaTime) override;
	virtual EditMonster4* Clone() override;

protected:
	EditMonster4();
	EditMonster4(const EditMonster4& Value);
	~EditMonster4();
};

