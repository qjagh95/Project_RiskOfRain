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

	//�Լ������� (���� �Ķ���������� �Լ��� �ּҸ� �Ű������� �ְڴ�)
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

	COLLIDER_TYPE m_CollType;   ///�浹Ÿ��(�簢��, ��, ��)
	Object* m_Object;			///�浹ü�� �ִ� ������Ʈ.
	string  m_GroupName;		///�ݱ׷� �̸�
	Vector2 m_Pivot;			///�߽���
	Vector2 m_CollsionPos;		///�浹�� ��ġ
	bool m_IsUI;

	//Ư���Լ����� ���� ó���ϸ� ���ǹ��� ������ ��������.... �׷��� �Լ������� ����Ʈ �迭
	list<function<void(Collider*, Collider*, float)>> m_CallBack[CS_COLMAX];
	list<Collider*> m_PrevCollList;	///���� �浹���
	string m_CollsionTypeName;

public:
	friend class Object;
	friend class CollsionManager;
};

