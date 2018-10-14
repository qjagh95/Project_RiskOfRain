#pragma once
#include "EditMonster.h"
class EditMonster6 : public EditMonster
{
public:
	friend class Object;

	bool Init() override;
	int Input(float DeltaTime) override;
	int Update(float DeltaTime) override;
	int LateUpdate(float DeltaTime) override;
	void Collision(float DeltaTime) override;
	void Render(HDC Hdc, float DeltaTime) override;
	EditMonster6* Clone() override;

protected:
	EditMonster6();
	EditMonster6(const EditMonster6& Value);
	~EditMonster6();
};

