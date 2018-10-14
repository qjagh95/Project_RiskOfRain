#pragma once
#include "EditMonster.h"
class EditMonster2 : public EditMonster
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	EditMonster2* Clone() override;

protected:
	EditMonster2();
	EditMonster2(const EditMonster2& Value);
	~EditMonster2();
};
