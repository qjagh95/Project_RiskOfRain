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
	//일단 두개의 그룹을 넣어준다.
	CreateCollsionGroup("Default");
	CreateCollsionGroup("UI");

	return true;
}

void CollsionManager::Collsion(float DeltaTime)
{
	//마우스대UI를 먼저 충돌해서 UI가 충돌될 경우 마우스와 월드공간 오브젝트와의 충돌처리를 하지 않는다
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

	// 마우스와 일반 오브젝트 충돌처리
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

				// 충돌 됐을 경우
				if (MouseColliderWorld->Collsion(pDest) == true)
				{
					isUICollsion = true;
					pDest->SetCollsionPos(MouseColliderWorld->GetCollsionPos());

					// 이전에 충돌했던 목록에 Dest가 없다면 처음 충돌한다는 것이다.
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

				// 충돌 안됐을 경우
				else
				{
					// 충돌이 안될때 만약 이전 충돌목록에 상대가 존재한다면
					// 충돌 하다가 떨어진다는 것이다.
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
		//충돌체 수만큼 반복한다 단 충돌체수가 1개이하일경우 충돌처리를 안해줘도된다.
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
				//충돌처리를 한다 단 같은 오브젝트에 속해있는 충돌체끼리는 걸러준다.
				Collider* Dest = newGroup->ColliderList[j];
				//충돌체를 가지고있는 오브젝트를 얻어온다
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

				//충돌을 했을경우
				if (Src->Collsion(Dest) == true)
				{
					//이전충돌목록에 Dest가 없으면 처음충돌했단의미
					if (Src->CheckPrevCollider(Dest) == false)
					{
						//이전컬라이더에 넣어준다
						Src->AddPrevCollider(Dest);
						Dest->AddPrevCollider(Src);

						//여기서 콜백함수들을 호출해준다.
						Src->OnCollsionFirst(Dest, DeltaTime);
						Dest->OnCollsionFirst(Src, DeltaTime);
					}
					else
					{
						//이전 목록에 뭔가가있다면 충돌중이라는 것
						Src->OnCollsionDoing(Dest, DeltaTime);
						Dest->OnCollsionDoing(Src, DeltaTime);
					}
				}
				//충돌을 안했을경우
				else
				{
					//만약 충돌이 안됬을때 이전 충돌상태가 존재한다면 충돌했다가 떨어졌다는뜻이다.
					if (Src->CheckPrevCollider(Dest) == true)
					{
						//이전 컬라이더 리스트에서 지워준다
						Src->DeletePrevCollider(Dest);
						Dest->DeletePrevCollider(Src);

						Src->OnCollsionEnd(Dest, DeltaTime);
						Dest->OnCollsionEnd(Src, DeltaTime);
					}
				} //else(충돌을 안했을때)
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

//레이어에서 계속 Object에 있는 충돌체리스트를 CollGroup안에있는 이중포인터배열에 넣어준다.
void CollsionManager::AddCollider(Object * pObject)
{
	//오브젝트가 가진 모든 충돌체를 넣어준다.
	const list<Collider*>* newColliderList = pObject->GetColliderList();

	//비어있다면 ㅂㅂ
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
		//컬라이더 안에있는 그룹이름을 가져온다.
		CollGroup* newGroup = FindColGroup((*StartIter)->GetCollsionGroupName());

		//그룹이 존재하지않는다면 추가할것이없다.
		if (newGroup == NULL)
			continue;

		//배열크기 재할당 과정
		if (newGroup->Size == newGroup->Capacity)
		{
			newGroup->Capacity *= 2;
			Collider** newColliderList = new Collider*[newGroup->Capacity];

			//새로만든 리스트에다 기존것을 복사하겠다.
			memcpy(newColliderList, newGroup->ColliderList, sizeof(Collider*) * newGroup->Size);

			SAFE_DELETE_ARRAY(newGroup->ColliderList);

			newGroup->ColliderList = newColliderList;
		}
		newGroup->ColliderList[newGroup->Size] = *StartIter;
		newGroup->Size++;
	}
}
