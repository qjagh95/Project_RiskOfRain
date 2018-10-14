#include "stdafx.h"
#include "Input.h"
#include "MouseObject.h"
#include "Camera.h"

INIT_STATIC_VAR(Input)

Input::Input()
	: KeyState(NULL), m_Mouse(NULL), m_isMouseShow(false)
{
}

Input::~Input()
{
	Safe_Delete_Map(KeyMap);
	SAFE_RELEASE(m_Mouse);
}

bool Input::Init()
{
	m_Mouse = new MouseObject();

	if (m_Mouse->Init() == false)
	{
		SAFE_RELEASE(m_Mouse);
		return false;
	}

	m_Mouse->SetSize(Vector2(32.0f, 31.0f));
	m_Mouse->SetTexture("Mouse", TEXT("Mouse/0.bmp"));
	m_Mouse->SetColorKey(RGB(255, 0, 255));

	//내부적으로 카운트방식으로 돌아간다.
	ShowCursor(FALSE);

	PushKey("LBotton", VK_LBUTTON);
	PushKey("RBotton", VK_RBUTTON);
	PushKey("MBotton", VK_MBUTTON);

	PushKey("Puase", VK_F5);
	PushKey("DebugOnOff", VK_F6);

	return true;
}

void Input::Update(float DeltaTime)
{
	unordered_map<string, KeyInfo*>::iterator	iterStart = KeyMap.begin();
	unordered_map<string, KeyInfo*>::iterator	iterEnd = KeyMap.end();

	for (; iterStart != iterEnd; iterStart++)
	{
		size_t Count = 0;

		for (size_t i = 0; i < iterStart->second->VecKey.size(); i++)
		{
			//GetAsyncKeyState() 함수는,
			//키가 눌려진 시점에서 0x8000 값을 리턴해 준다.
			//그리고 함수가 호출되었을때 키가 눌려져 있었다고 0x0001 값을 리턴해 준다.
			//즉, 0x8000 은 현재 키가 눌려진 상태를 뜻하고,
			//0x0001은 지난번 호출과 이번 호출 사이에 키가 눌려진 적이 있었다 라는 것을 뜻한다.
			if (GetAsyncKeyState(iterStart->second->VecKey[i]) & 0x8000)
				Count++;
		}


		//카운트가 사이즈와 같다는것은 다 돌았다는 뜻이다.
		if (iterStart->second->VecKey.size() == Count)
		{
			if (iterStart->second->KeyDown == false && iterStart->second->KeyPress == false)
			{
				iterStart->second->KeyDown = true;
				iterStart->second->KeyPress = true;
			}

			else if (iterStart->second->KeyDown == true)
				iterStart->second->KeyDown = false;
		}

		else if (iterStart->second->KeyPress == true)
		{
			iterStart->second->KeyUp = true;
			iterStart->second->KeyDown = false;
			iterStart->second->KeyPress = false;
		}

		else if (iterStart->second->KeyUp == true)
			iterStart->second->KeyUp = false;
	}

	POINT mPos;

	GetCursorPos(&mPos);
	ScreenToClient(Core::Get()->GetHwnd(), &mPos);

	m_MouseGap.x = mPos.x - m_MouseScreenPos.x;
	m_MouseGap.y = mPos.y - m_MouseScreenPos.y;

	//스크린좌표
	m_MouseScreenPos = mPos;

	//카메라가 적용된 좌표로 바꿔준다.
	m_MouseWorldPos = m_MouseScreenPos + Camera::Get()->GetPos();
	m_Mouse->SetPos(m_MouseWorldPos);

	m_Mouse->Update(DeltaTime);
	m_Mouse->LateUpdate(DeltaTime);

	//범위밖을나가면 커서를 보여주고 아니면 안보여준다.
	if (m_isMouseShow == false && (m_MouseScreenPos.x < 0.0f || m_MouseScreenPos.x > Core::Get()->GetWinSize().Width || m_MouseScreenPos.y < 0.0f || m_MouseScreenPos.y > Core::Get()->GetWinSize().Height))
	{
		m_isMouseShow = true;

		while (ShowCursor(TRUE) != 0)
		{
		}
	}
	else if(m_isMouseShow == true && (m_MouseScreenPos.x >= 0.0f && m_MouseScreenPos.x <= Core::Get()->GetWinSize().Width && m_MouseScreenPos.y >= 0.0f && m_MouseScreenPos.y <= Core::Get()->GetWinSize().Height))
	{
		m_isMouseShow = false;
		
		while (ShowCursor(FALSE) >= 0)
		{
		}
	}
}

void Input::RenderMouse(HDC hDC, float DeltaTime)
{
	m_Mouse->Render(hDC, DeltaTime);

	if (Core::Get()->GetIsDebugMode() == false)
		return;

	TCHAR Buffer[255] = {};
	swprintf_s(Buffer, L"MouseScreenPos : %f, %f", m_MouseScreenPos.x, m_MouseScreenPos.y);
	TextOutW(hDC, 0, 60, Buffer, lstrlen(Buffer));

	swprintf_s(Buffer, L"MouseWorldPos : %f, %f", m_MouseWorldPos.x, m_MouseWorldPos.y);
	TextOutW(hDC, 0, 80, Buffer, lstrlen(Buffer));

	swprintf_s(Buffer, L"MouseGap : %f, %f", m_MouseGap.x, m_MouseGap.y);
	TextOutW(hDC, 0, 100, Buffer, lstrlen(Buffer));
}

bool Input::KeyDown(const string& Name)
{
	KeyInfo* fKey = FindKey(Name);

	if (fKey == NULL)
		return false;

	return fKey->KeyDown;
}

bool Input::KeyPress(const string& Name)
{
	KeyInfo* fKey = FindKey(Name);

	if (fKey == NULL)
		return false;

	return fKey->KeyPress;
}

bool Input::KeyUp(const string& Name)
{
	KeyInfo* fKey = FindKey(Name);

	if (fKey == NULL)
		return false;

	return fKey->KeyUp;
}

void Input::SetMouseTexture(Texture * mTexture)
{
	m_Mouse->SetTexture(mTexture);
}

void Input::SetMouseTextureSize(float x, float y)
{
	m_Mouse->SetSize(x, y);
}

void Input::SetMouseTextureSize(const Vector2 & Pos)
{
	m_Mouse->SetSize(Pos);
}

void Input::SetMouseTexturePivot(float x, float y)
{
	m_Mouse->SetPivot(x, y);
}

void Input::SetMouseTexturePivot(const Vector2 & Pos)
{
	m_Mouse->SetPivot(Pos);
}

Texture * Input::GetMouseTexture() const
{
	return m_Mouse->m_Texture;
}

void Input::SetMouseDefaultTexture()
{
	m_Mouse->SetSize(Vector2(32.0f, 31.0f));
	m_Mouse->SetPivot(0.0f, 0.0f);
	m_Mouse->SetTexture("Mouse", TEXT("Mouse/0.bmp"));
}

KeyInfo* Input::FindKey(const string & Name)
{
	unordered_map <string, KeyInfo*>::iterator FindIter = KeyMap.find(Name);

	if (FindIter == KeyMap.end())
		return NULL;

	return FindIter->second;
}
