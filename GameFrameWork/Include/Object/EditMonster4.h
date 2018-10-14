#pragma once
#include "EditMonster.h"
class EditMonster4 : public EditMonster
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	EditMonster4* Clone() override;

protected:
	EditMonster4();
	EditMonster4(const EditMonster4& Value);
	~EditMonster4();
};

