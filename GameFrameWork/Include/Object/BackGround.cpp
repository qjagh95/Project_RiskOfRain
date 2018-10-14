#include "BackGround.h"
#include "../Camera.h"
#include "../Resource/Texture.h"

BackGround::BackGround()
{
	m_ObjectType = OT_BACKGROUND;
	SetTag("BackGorund");
}

BackGround::BackGround(const BackGround & Value)
	:Object(Value)
{
}

BackGround::~BackGround()
{
}

bool BackGround::Init()
{
	SetPos(0.0f, 0.0f);
	SetSize(1280.0f , 720.0f);
	SetPivot(0.0f, 0.0f);

	SetTexture("Stage1", L"Stage1.bmp");

	return true;
}

int BackGround::Input(float DeltaTime)
{
	Object::Input(DeltaTime);

	return 0;
}

int BackGround::Update(float DeltaTime)
{
	Object::Update(DeltaTime);

	return 0;
}

int BackGround::LateUpdate(float DeltaTime)
{
	Object::LateUpdate(DeltaTime);

	return 0;
}

void BackGround::Collision(float DeltaTime)
{
	Object::Collision(DeltaTime);
}

void BackGround::Render(HDC Hdc, float DeltaTime)
{
	CameraPos = Camera::Get()->GetPos();

	TransparentBlt(Hdc, 0, 0,(int)m_Size.x, (int)m_Size.y, m_Texture->GetMemDC(), (int)CameraPos.x, (int)CameraPos.y, (int)m_Size.x, (int)m_Size.y, m_ColorKey);
}

BackGround * BackGround::Clone()
{
	return new BackGround(*this);
}
