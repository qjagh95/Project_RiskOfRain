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

	template <typename T>
	bool PushKey(const T& value)
	{
		const char* pType = typeid(T).name();

		if (strcmp(pType, "int") == 0 || strcmp(pType, "char") == 0)
			KeyState->VecKey.push_back((DWORD&)value);

		else
		{
			KeyState->Name = value;
			KeyMap.insert(make_pair(KeyState->Name, KeyState));
		}
		return true;
	}

	template <typename T, typename ... Types>
	bool PushKey(const T& value, Types ... Args)
	{
		if (!KeyState)
		{
			KeyState = new KeyInfo();
			KeyState->KeyPress = false;
			KeyState->KeyDown = false;
			KeyState->KeyUp = false;
		}

		const char* pType = typeid(T).name();

		if (strcmp(pType, "int") == 0 || strcmp(pType, "char") == 0)
			KeyState->VecKey.push_back((DWORD&)value);
		else
		{
			KeyState->Name = value;
			KeyMap.insert(make_pair(KeyState->Name, KeyState));
		}

		PushKey(Args...);

		if (KeyState)
			KeyState = nullptr;

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

