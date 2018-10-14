#pragma once
#include "Collider.h"

//충돌체는 일반적인 배열을 이용해서 하는것이
//STL을 쓰는것보다 훨씬빠르다
class Object;
class CollsionManager
{
private:
	struct CollGroup
	{
		//Object가 충돌체 리스트의 포인터주소를 가지고있기때문에 그 포인터의 주소를 받기위하여 이중포인터
		Collider** ColliderList;
		int Capacity;			///배열크기
		int Size;				///채워진크기
		string GroupName;

		CollGroup() : Capacity(100), Size(0) { ColliderList = new Collider*[Capacity]; }
		~CollGroup() { SAFE_DELETE_ARRAY(ColliderList); }
	};

public:
	bool Init();
	void Collsion(float DeltaTime);

	bool CreateCollsionGroup(const string& GroupName);
	CollGroup* FindColGroup(const string& GroupName);
	void AddCollider(Object* pObject);

private:
	unordered_map<string, CollGroup*> m_CollGroupMap;

public:
	CLASS_IN_SINGLE(CollsionManager)
};

