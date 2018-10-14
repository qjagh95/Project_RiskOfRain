#pragma once

struct KeyInfo
{
	vector<DWORD> VecKey;
	string Name;
	bool KeyDown;
	bool KeyPress;
	bool KeyUp;
};

class MouseObject;
class Input
{
public:
	bool KeyDown(const string& Name);
	bool KeyPress(const string& Name);
	bool KeyUp(const string& Name);

	bool Init();
	void Update(float DeltaTime);
	void RenderMouse(HDC hDC, float DeltaTime);

	//종료조건 함수를 만든다
	template<typename T>
	bool PushKey(T& Value)
	{
		//한개짜리키는 여기 벡터에서 푸시빾
		DWORD dKey = (DWORD&)Value;
		KeyState->VecKey.push_back(dKey);

		return true;
	}
	//베리어딕 템플릿 (템플릿가변인자)
	template<typename T, typename ...Types>
	bool PushKey(T& Value, Types ...arg)
	{
		//들어온것의 타입이름을 리턴해주는 함수
		const char* pType = typeid(T).name();

		if (KeyState == NULL)
		{
			KeyState = new KeyInfo();

			KeyState->KeyDown = false;
			KeyState->KeyPress = false;
			KeyState->KeyUp = false;
		}
		//VK와 일반 a, b .. 등을 구분하기 위함
		if (strcmp(pType, "int") == 0 || strcmp(pType, "char") == 0)
		{
			DWORD dKey = (DWORD&)Value;
			KeyState->VecKey.push_back(dKey);
		}
		else
		{
			KeyState->Name = Value;
			KeyMap.insert(make_pair(KeyState->Name, KeyState));
		}

		PushKey(arg...);

		if (KeyState != NULL)
			KeyState = NULL;

		return true;
	}

	Vector2 GetMouseWorldPos() const { return m_MouseWorldPos; }
	Vector2 GetMouseScreenPos() const { return m_MouseScreenPos; }
	Vector2 GetMouseGap() const { return m_MouseGap; }
	MouseObject* GetMouseObject() const { return m_Mouse; }
	void SetMouseTexture(Texture* mTexture);
	void SetMouseTextureSize(float x, float y);
	void SetMouseTextureSize(const Vector2& Pos);
	void SetMouseTexturePivot(float x, float y);
	void SetMouseTexturePivot(const Vector2& Pos);
	Texture* GetMouseTexture() const;
	void SetMouseDefaultTexture();

private:
	KeyInfo* FindKey(const string& Name);

	unordered_map <string, KeyInfo*> KeyMap;
	KeyInfo *KeyState; ///맵에 넣어주기 위한 변수

	Vector2 m_MouseWorldPos;
	Vector2 m_MouseScreenPos;
	Vector2 m_MouseGap; ///얼마나 움직였어?
	MouseObject* m_Mouse;
	bool m_isMouseShow;

private:
	CLASS_IN_SINGLE(Input)
};

