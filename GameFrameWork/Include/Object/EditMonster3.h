#pragma once
#include "EditMonster.h"
class EditMonster3 : public EditMonster
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	EditMonster3* Clone() override;

protected:
	EditMonster3();
	EditMonster3(const EditMonster3& Value);
	~EditMonster3();
};

