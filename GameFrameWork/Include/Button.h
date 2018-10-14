#pragma once
#include "UI.h"
class Texture;
class ColliderRect;
class Button : public UI
{
public:
	bool Init();
	int Input(float DeltaTime);
	int Update(float DeltaTime);
	int LateUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(HDC hDC, float DeltaTime);
	Button* Clone();

	void OnCollsionFirst(Collider* Src, Collider* Dest, float DeltaTime);
	void OnCollsionDoing(Collider* Src, Collider* Dest, float DeltaTime);
	void OnCollsionEnd(Collider* Src, Collider* Dest, float DeltaTime);

	void SetIsOffset(bool Value) { m_isOffset = Value; }
	void SetCallBack(void(*pFunc)(float));
	template<typename T>
	void SetCallBack(void(T::*pFunc)(float), T* pObject)
	{
		m_isCallBack = true;
		m_ClickCallBack = bind(pFunc, pObject, placeholders::_1);
	}

protected:
	Button();
	Button(const Button& ui);
	~Button();

private:
	BUTTON_STATE m_ButtonState;
	bool m_isCallBack;
	function<void(float)> m_ClickCallBack;
	bool m_isOffset;

	ColliderRect* RC;

public:
	friend class Object;
};