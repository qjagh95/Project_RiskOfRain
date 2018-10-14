#pragma once
#include "../RefCount.h"

class Object;
class Collider : public RefCount
{
public:
	virtual bool Init();
	virtual int Update(float DeltaTime);
	virtual bool Collsion(Collider* Dest) = 0;
	virtual void Render(HDC hDC, float DeltaTime);
	virtual Collider* Clone() const;
	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);

	COLLIDER_TYPE GetCollType() const { return m_CollType; }
	void SetPivot(const Vector2& Value) { m_Pivot = Value; }
	void SetPivot(float Value1, float Value2) { m_Pivot.x = Value1, m_Pivot.y = Value2; }
	Object* GetCurObject() const;
	void SetObject(Object* Value) { m_Object = Value; }
	void SetCollsionGroupName(const string& GroupName) { this->m_GroupName = GroupName; }
	string GetCollsionGroupName() const { return m_GroupName; }

	void OnCollsionFirst(Collider* pDest, float DeltaTime);
	void OnCollsionDoing(Collider* pDest, float DeltaTime);
	void OnCollsionEnd(Collider* pDest, float DeltaTime);

	//함수포인터 (위의 파라미터형식의 함수의 주소를 매개변수로 넣겠다)
	void SetCallBack(void(*pFunc)(Collider*, Collider*, float), COLLSION_STATE Type)
	{
		m_CallBack[Type].push_back(bind(pFunc, placeholders::_1, placeholders::_2, placeholders::_3));
	}
	template<typename T>
	void SetCallBack(T* pObject, void(T::*pFunc)(Collider*, Collider*, float), COLLSION_STATE Type)
	{
		m_CallBack[Type].push_back(bind(pFunc, pObject, placeholders::_1, placeholders::_2, placeholders::_3));
	}

	void AddPrevCollider(Collider* Value) { m_PrevCollList.push_back(Value); }

	void DeletePrevCollider(Collider* Value)
	{
		list<Collider*>::iterator	StartIter = m_PrevCollList.begin();
		list<Collider*>::iterator	EndIter = m_PrevCollList.end();

		for (; StartIter != EndIter; StartIter++)
		{
			if (*StartIter == Value)
			{  
				m_PrevCollList.erase(StartIter);
				return;
			}
		}
	}

	void DeletePrevCollider()
	{
		list<Collider*>::iterator	StartIter = m_PrevCollList.begin();
		list<Collider*>::iterator	EndIter = m_PrevCollList.end();

		for (; StartIter != EndIter; StartIter++)
		{
			(*StartIter)->DeletePrevCollider(this);
			OnCollsionEnd(*StartIter, 0.0f);
			(*StartIter)->OnCollsionEnd(this, 0.0f);
		}

		m_PrevCollList.clear();
	}

	bool CheckPrevCollider(Collider* Value)
	{
		list<Collider*>::iterator	StartIter = m_PrevCollList.begin();
		list<Collider*>::iterator	EndIter = m_PrevCollList.end();

		for (; StartIter != EndIter; StartIter++)
		{
			if (*StartIter == Value)
				return true;
		}
		return false;
	}

	void SetCollsionTypeName(const string& Name) { m_CollsionTypeName = Name; }
	string GetCollsionTypeName() const { return m_CollsionTypeName; }
	Vector2 GetPos() const;
	Vector2 GetCollsionPos() const { return m_CollsionPos; }
	bool GetIsUI() const { return m_IsUI; }
	void SetIsUI(bool Value) { m_IsUI = Value; }
	void SetCollsionPos(const Vector2& Value) { m_CollsionPos = Value; }
	void SetCollsionPos(float x, float y) { m_CollsionPos = Vector2(x, y); }

protected:
	bool CollsionRectToRect(const Rect& Left, const Rect& Right);
	bool CollsionCircleToCircle(const Circle& Left, const Circle& Right);
	bool CollsionRectToCircle(const Rect& Left, const Circle& Right);
	bool CollsionRectToPoint(const Rect& Left, const Vector2& Right);
	bool CollsionPointToPoint(const Vector2& Left, const Vector2& Right);
	bool CollsionCircleToPoint(const Circle& Left, const Vector2& Right);
	bool CollsionRectToPixel(const Rect& Left, const PixelInfo& Right);

protected:
	Collider();
	Collider(const Collider& Value);
	virtual ~Collider() = 0;

	COLLIDER_TYPE m_CollType;   ///충돌타입(사각형, 원, 점)
	Object* m_Object;			///충돌체가 있는 오브젝트.
	string  m_GroupName;		///콜그룹 이름
	Vector2 m_Pivot;			///중심점
	Vector2 m_CollsionPos;		///충돌된 위치
	bool m_IsUI;

	//특정함수에다 모든걸 처리하면 조건문이 굉장히 많아져용.... 그래서 함수포인터 리스트 배열
	list<function<void(Collider*, Collider*, float)>> m_CallBack[CS_COLMAX];
	list<Collider*> m_PrevCollList;	///이전 충돌목록
	string m_CollsionTypeName;

public:
	friend class Object;
	friend class CollsionManager;
};

