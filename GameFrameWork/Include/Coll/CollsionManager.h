#pragma once
#include "Collider.h"

//�浹ü�� �Ϲ����� �迭�� �̿��ؼ� �ϴ°���
//STL�� ���°ͺ��� �ξ�������
class Object;
class CollsionManager
{
private:
	struct CollGroup
	{
		//Object�� �浹ü ����Ʈ�� �������ּҸ� �������ֱ⶧���� �� �������� �ּҸ� �ޱ����Ͽ� ����������
		Collider** ColliderList;
		int Capacity;			///�迭ũ��
		int Size;				///ä����ũ��
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

