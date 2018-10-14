#pragma once
#include "Object.h"
class ColliderRect;
class EditMonster : public Object
{
public:
	friend class Object;

	virtual bool Init();
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC Hdc, float DeltaTime);
	virtual EditMonster* Clone();
	
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

