#pragma once
#include "../Object/EditMonster.h"

class EditMonster1 : public EditMonster
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	EditMonster1* Clone() override;

protected:
	EditMonster1();
	EditMonster1(const EditMonster1& Value);
	~EditMonster1();
};

