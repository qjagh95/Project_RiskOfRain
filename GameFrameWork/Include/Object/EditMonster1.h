#pragma once
#include "../Object/EditMonster.h"

class EditMonster1 : public EditMonster
{
public:
	friend class Object;

	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void Render(HDC Hdc, float DeltaTime) override;
	virtual EditMonster1* Clone() override;

protected:
	EditMonster1();
	EditMonster1(const EditMonster1& Value);
	~EditMonster1();
};

