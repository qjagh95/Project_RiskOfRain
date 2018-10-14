#pragma once
#include "EditMonster.h"
class EditMonster5 : public EditMonster
{
public:
	friend class Object;

	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void Render(HDC Hdc, float DeltaTime) override;
	virtual EditMonster5* Clone() override;

protected:
	EditMonster5();
	EditMonster5(const EditMonster5& Value);
	~EditMonster5();
};

