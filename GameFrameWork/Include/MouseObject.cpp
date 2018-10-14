#include "MouseObject.h"
#include "Coll\ColliderPoint.h"
#include "Input.h"

MouseObject::MouseObject()
{
	SetTag("MouseObject");
}

MouseObject::MouseObject(const MouseObject & mouse)
	:Object(mouse)
{
	m_isLBotton = mouse.m_isLBotton;
	m_isRBotton = mouse.m_isRBotton;
	m_isMBotton = mouse.m_isMBotton;
}

MouseObject::~MouseObject()
{
}

bool MouseObject::Init()
{
	if (Object::Init() == false)
		return false;

	m_isLBotton = false;
	m_isRBotton = false;
	m_isMBotton = false;

	//中宜端 持失
	ColliderPoint* pPoint = AddCollider<ColliderPoint>("MouseObject");
	SAFE_RELEASE(pPoint);

	pPoint = AddCollider<ColliderPoint>("MouseObjectUI");
	pPoint->SetIsUI(true);
	
	SAFE_RELEASE(pPoint);

	return true;
}

int MouseObject::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	if (KEYDOWN("LBotton"))
		m_isLBotton = true;
	else if (KEYUP("LBotton"))
		m_isLBotton = false;

	if (KEYDOWN("RBotton"))
		m_isRBotton = true;
	else if (KEYUP("RBotton"))
		m_isRBotton = false;

	if (KEYDOWN("MBotton"))
		m_isMBotton = true;
	else if (KEYUP("MBotton"))
		m_isMBotton = false;

	return 0;
}

int MouseObject::Update(float DeltaTime)
{
	Object::Update(DeltaTime);
	return 0;
}

int MouseObject::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void MouseObject::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void MouseObject::Render(HDC hDC, float DeltaTime)
{
	Object::Render(hDC, DeltaTime);
}

MouseObject * MouseObject::Clone()
{
	return new MouseObject(*this);
}
