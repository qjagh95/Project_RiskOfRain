#pragma once
#include "Object.h"
class ColliderRect;
class EditMonster : public Object
{
public:
	friend class Object;

	virtual bool Init() override;
	virtual int Input(float DeltaTime) override;
	virtual int Update(float DeltaTime) override;
	virtual int LateUpdate(float DeltaTime) override;
	virtual void Collision(float DeltaTime) override;
	virtual void Render(HDC Hdc, float DeltaTime) override;
	virtual EditMonster* Clone() override;
	
	void MouseHit(Collider * Src, Collider * Dest, float DeltaTime);
	static bool GetIsSelect() { return isSelect; }

protected:
	EditMonster();
	EditMonster(const EditMonster& Value);
	virtual ~EditMonster();

	ColliderRect* RC;
	static EditMonster* EditSelect;
	static bool isSelect;
	bool	m_bDrag;
};

