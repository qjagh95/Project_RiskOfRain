#include "CollsionManager.h"
#include "../Object/Object.h"
#include "../Input.h"

INIT_STATIC_VAR(CollsionManager)

CollsionManager::CollsionManager()
{
}

CollsionManager::~CollsionManager()
{
	Safe_Delete_Map(m_CollGroupMap);
}

bool CollsionManager::Init()
{
	//�ϴ� �ΰ��� �׷��� �־��ش�.
	CreateCollsionGroup("Default");
	CreateCollsionGroup("UI");

	return true;
}

void CollsionManager::Collsion(float DeltaTime)
{
	//���콺��UI�� ���� �浹�ؼ� UI�� �浹�� ��� ���콺�� ������� ������Ʈ���� �浹ó���� ���� �ʴ´�
	bool isUICollsion = false;
	Object* MouseObj = (Object*)Input::Get()->GetMouseObject();
	Collider* MouseCollider = MouseObj->GetCollider("MouseObjectUI");
	Collider* MouseColliderWorld = MouseObj->GetCollider("MouseObject");
	CollGroup* UiCollGroup = FindColGroup("UI");

	if (UiCollGroup != NULL)
	{
		for (int i = 0; i < UiCollGroup->Size; ++i)
		{
			if (isUICollsion == true)
				break;

			Collider* pDest = UiCollGroup->ColliderList[i];

			if (MouseCollider->Collsion(pDest) == true)
			{
				isUICollsion = true;
				pDest->SetCollsionPos(MouseCollider->GetCollsionPos());

				if (MouseCollider->CheckPrevCollider(pDest) == false)
				{
					MouseCollider->DeletePrevCollider();
					MouseColliderWorld->DeletePrevCollider();

					MouseCollider->AddPrevCollider(pDest);
					pDest->AddPrevCollider(MouseCollider);

					MouseCollider->OnCollsionFirst(pDest, DeltaTime);
					pDest->OnCollsionFirst(MouseCollider, DeltaTime);
				}
				else
				{
					MouseCollider->OnCollsionDoing(pDest, DeltaTime);
					pDest->OnCollsionDoing(MouseCollider, DeltaTime);
				}
			}
			else
			{
				if (MouseCollider->CheckPrevCollider(pDest))
				{
					MouseCollider->DeletePrevCollider(pDest);
					pDest->DeletePrevCollider(MouseCollider);

					MouseCollider->OnCollsionEnd(pDest, DeltaTime);
					pDest->OnCollsionEnd(MouseCollider, DeltaTime);
				}
			}
		}
	}
	SAFE_RELEASE(MouseCollider);

	// ���콺�� �Ϲ� ������Ʈ �浹ó��
	if (isUICollsion == false)
	{
		unordered_map<string, CollGroup*>::iterator	StartIter = m_CollGroupMap.begin();
		unordered_map<string, CollGroup*>::iterator	iterEnd = m_CollGroupMap.end();

		for (; StartIter != iterEnd; ++StartIter)
		{
			if (StartIter->first == "UI")
				continue;

			UiCollGroup = StartIter->second;

			for (int i = 0; i < UiCollGroup->Size; ++i)
			{
				if (isUICollsion == true)
					break;

				Collider*	pDest = UiCollGroup->ColliderList[i];

				// �浹 ���� ���
				if (MouseColliderWorld->Collsion(pDest) == true)
				{
					isUICollsion = true;
					pDest->SetCollsionPos(MouseColliderWorld->GetCollsionPos());

					// ������ �浹�ߴ� ��Ͽ� Dest�� ���ٸ� ó�� �浹�Ѵٴ� ���̴�.
					if (!MouseColliderWorld->CheckPrevCollider(pDest))
					{
						MouseColliderWorld->AddPrevCollider(pDest);
						pDest->AddPrevCollider(MouseColliderWorld);

						MouseColliderWorld->OnCollsionFirst(pDest, DeltaTime);
						pDest->OnCollsionFirst(MouseColliderWorld, DeltaTime);
					}
					else
					{
						MouseColliderWorld->OnCollsionDoing(pDest, DeltaTime);
						pDest->OnCollsionDoing(MouseColliderWorld, DeltaTime);
					}
				}

				// �浹 �ȵ��� ���
				else
				{
					// �浹�� �ȵɶ� ���� ���� �浹��Ͽ� ��밡 �����Ѵٸ�
					// �浹 �ϴٰ� �������ٴ� ���̴�.
					if (MouseColliderWorld->CheckPrevCollider(pDest))
					{
						MouseColliderWorld->DeletePrevCollider(pDest);
						pDest->DeletePrevCollider(MouseColliderWorld);

						MouseColliderWorld->OnCollsionEnd(pDest, DeltaTime);
						pDest->OnCollsionEnd(MouseColliderWorld, DeltaTime);
					}
				}
			}
		}
	}
	SAFE_RELEASE(MouseColliderWorld);
	SAFE_RELEASE(MouseCollider);

	unordered_map<string, CollGroup*>::iterator StartIter = m_CollGroupMap.begin();
	unordered_map<string, CollGroup*>::iterator EndIter = m_CollGroupMap.end();

	for (; StartIter != EndIter; StartIter++)
	{
		//�浹ü ����ŭ �ݺ��Ѵ� �� �浹ü���� 1�������ϰ�� �浹ó���� �����൵�ȴ�.
		CollGroup* newGroup = StartIter->second;

		if (newGroup->Size < 2)
		{
			newGroup->Size = 0;
			continue;
		}

		for (int i = 0; i < newGroup->Size - 1; i++)
		{
			Collider* Src = newGroup->ColliderList[i];
			Object* SrcObj = Src->GetCurObject();

			for (int j = i + 1; j < newGroup->Size; j++)
			{
				//�浹ó���� �Ѵ� �� ���� ������Ʈ�� �����ִ� �浹ü������ �ɷ��ش�.
				Collider* Dest = newGroup->ColliderList[j];
				//�浹ü�� �������ִ� ������Ʈ�� ���´�
				Object* DestObj = Dest->GetCurObject();

				if (Src->GetCollsionTypeName() == Dest->GetCollsionTypeName())
				{
					SAFE_RELEASE(DestObj);
					continue;
				}

				if (SrcObj == DestObj)
				{
					SAFE_RELEASE(DestObj);
					continue;
				}

				SAFE_RELEASE(DestObj);

				//�浹�� �������
				if (Src->Collsion(Dest) == true)
				{
					//�����浹��Ͽ� Dest�� ������ ó���浹�ߴ��ǹ�
					if (Src->CheckPrevCollider(Dest) == false)
					{
						//�����ö��̴��� �־��ش�
						Src->AddPrevCollider(Dest);
						Dest->AddPrevCollider(Src);

						//���⼭ �ݹ��Լ����� ȣ�����ش�.
						Src->OnCollsionFirst(Dest, DeltaTime);
						Dest->OnCollsionFirst(Src, DeltaTime);
					}
					else
					{
						//���� ��Ͽ� �������ִٸ� �浹���̶�� ��
						Src->OnCollsionDoing(Dest, DeltaTime);
						Dest->OnCollsionDoing(Src, DeltaTime);
					}
				}
				//�浹�� ���������
				else
				{
					//���� �浹�� �ȉ����� ���� �浹���°� �����Ѵٸ� �浹�ߴٰ� �������ٴ¶��̴�.
					if (Src->CheckPrevCollider(Dest) == true)
					{
						//���� �ö��̴� ����Ʈ���� �����ش�
						Src->DeletePrevCollider(Dest);
						Dest->DeletePrevCollider(Src);

						Src->OnCollsionEnd(Dest, DeltaTime);
						Dest->OnCollsionEnd(Src, DeltaTime);
					}
				} //else(�浹�� ��������)
			}//for(j)
			SAFE_RELEASE(SrcObj);
		}//for(i)
		newGroup->Size = 0;
	}//for(Iter)
}

bool CollsionManager::CreateCollsionGroup(const string & GroupName)
{
	CollGroup* newGroup = FindColGroup(GroupName);

	if (newGroup != NULL)
		return false;

	newGroup = new CollGroup();

	m_CollGroupMap.insert(make_pair(GroupName, newGroup));

	return true;
}

CollsionManager::CollGroup * CollsionManager::FindColGroup(const string & GroupName)
{
	unordered_map<string, CollGroup*>::iterator FindIter = m_CollGroupMap.find(GroupName);

	if (FindIter == m_CollGroupMap.end())
		return NULL;

	return FindIter->second;
}

//���̾�� ��� Object�� �ִ� �浹ü����Ʈ�� CollGroup�ȿ��ִ� ���������͹迭�� �־��ش�.
void CollsionManager::AddCollider(Object * pObject)
{
	//������Ʈ�� ���� ��� �浹ü�� �־��ش�.
	const list<Collider*>* newColliderList = pObject->GetColliderList();

	//����ִٸ� ����
	if (newColliderList->empty() == true)
		return;

	list<Collider*>::const_iterator StartIter = newColliderList->begin();
	list<Collider*>::const_iterator EndIter = newColliderList->end();

	for (; StartIter != EndIter; StartIter++)
	{
		if ((*StartIter)->GetisShow() == false)
		{
			(*StartIter)->DeletePrevCollider();
			continue;
		}
		//�ö��̴� �ȿ��ִ� �׷��̸��� �����´�.
		CollGroup* newGroup = FindColGroup((*StartIter)->GetCollsionGroupName());

		//�׷��� ���������ʴ´ٸ� �߰��Ұ��̾���.
		if (newGroup == NULL)
			continue;

		//�迭ũ�� ���Ҵ� ����
		if (newGroup->Size == newGroup->Capacity)
		{
			newGroup->Capacity *= 2;
			Collider** newColliderList = new Collider*[newGroup->Capacity];

			//���θ��� ����Ʈ���� �������� �����ϰڴ�.
			memcpy(newColliderList, newGroup->ColliderList, sizeof(Collider*) * newGroup->Size);

			SAFE_DELETE_ARRAY(newGroup->ColliderList);

			newGroup->ColliderList = newColliderList;
		}
		newGroup->ColliderList[newGroup->Size] = *StartIter;
		newGroup->Size++;
	}
}
