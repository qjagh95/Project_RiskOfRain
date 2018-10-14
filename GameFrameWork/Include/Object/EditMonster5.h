#pragma once
#include "EditMonster.h"
class EditMonster5 : public EditMonster
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	EditMonster5* Clone() override;

protected:
	EditMonster5();
	EditMonster5(const EditMonster5& Value);
	~EditMonster5();
};

