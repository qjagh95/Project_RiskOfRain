#include "../stdafx.h"
#include "Layer.h"
#include "../Object/Object.h"
#include "../Coll/CollsionManager.h"

Layer::Layer()
	:m_Scene(NULL), Zorder(0)
{
}

Layer::~Layer()
{
	Safe_Release_VecList(LayerObjectList);
}

bool Layer::Init()
{
	return true;
}

int Layer::Input(float DeltaTime)
{
	list<Object*>::iterator StartIter = LayerObjectList.begin();
	list<Object*>::iterator EndIter = LayerObjectList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			//탐색리스트에서도 지워준다.
			Object::EraseSceneObject((*StartIter)->GetTag(), *StartIter);
			SAFE_RELEASE((*StartIter));
			StartIter = LayerObjectList.erase(StartIter);
			EndIter = LayerObjectList.end();
			continue;
		}
		//데이터상으론 존재한다. 하지만 보여주진않겠다!
		else if ((*StartIter)->GetisShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->Input(DeltaTime);
		StartIter++;
	}

	return 0;
}

int Layer::Update(float DeltaTime)
{
	list<Object*>::iterator StartIter = LayerObjectList.begin();
	list<Object*>::iterator EndIter = LayerObjectList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			//탐색리스트에서도 지워준다.
			Object::EraseSceneObject((*StartIter)->GetTag(), *StartIter);
			SAFE_RELEASE((*StartIter));
			StartIter = LayerObjectList.erase(StartIter);
			EndIter = LayerObjectList.end();
			continue;
		}
		//데이터상으론 존재한다. 하지만 보여주진않겠다!
		else if ((*StartIter)->GetisShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->Update(DeltaTime);
		StartIter++;
	}
	return 0;
}

int Layer::LateUpdate(float DeltaTime)
{
	list<Object*>::iterator StartIter = LayerObjectList.begin();
	list<Object*>::iterator EndIter = LayerObjectList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			//탐색리스트에서도 지워준다.
			Object::EraseSceneObject((*StartIter)->GetTag(), *StartIter);
			SAFE_RELEASE((*StartIter));

			StartIter = LayerObjectList.erase(StartIter);
			EndIter = LayerObjectList.end();
			continue;
		}
		//데이터상으론 존재한다. 하지만 보여주진않겠다!
		else if ((*StartIter)->GetisShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->LateUpdate(DeltaTime);
		StartIter++;
	}
	return 0;
}

void Layer::Collision(float DeltaTime)
{
	list<Object*>::iterator StartIter = LayerObjectList.begin();
	list<Object*>::iterator EndIter = LayerObjectList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			//탐색리스트에서도 지워준다.
			Object::EraseSceneObject((*StartIter)->GetTag(), *StartIter);
			SAFE_RELEASE((*StartIter));
			StartIter = LayerObjectList.erase(StartIter);
			EndIter = LayerObjectList.end();
			continue;
		}
		//데이터상으론 존재한다. 하지만 보여주진않겠다!
		else if ((*StartIter)->GetisShow() == false)
		{
			StartIter++;
			continue;
		}

		//오브젝트가 가지고있는 모든 충돌체 Collider를 Manager에있는 변수에 넣어준다.
		CollsionManager::Get()->AddCollider((*StartIter));
		StartIter++;
	}
}

void Layer::CollsionAfterUpdate(float DeltaTime)
{
	list<Object*>::iterator StartIter = LayerObjectList.begin();
	list<Object*>::iterator EndIter = LayerObjectList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			//탐색리스트에서도 지워준다.
			Object::EraseSceneObject((*StartIter)->GetTag(), *StartIter);
			SAFE_RELEASE((*StartIter));
			StartIter = LayerObjectList.erase(StartIter);
			EndIter = LayerObjectList.end();
			continue;
		}
		//데이터상으론 존재한다. 하지만 보여주진않겠다!
		else if ((*StartIter)->GetisShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->CollsionAfterUpdate(DeltaTime);
		StartIter++;
	}
}

void Layer::Render(HDC Hdc, float DeltaTime)
{
	list<Object*>::iterator StartIter = LayerObjectList.begin();
	list<Object*>::iterator EndIter = LayerObjectList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			//탐색리스트에서 지워준다
			Object::EraseSceneObject((*StartIter)->GetTag(), *StartIter);
			SAFE_RELEASE((*StartIter));
			StartIter = LayerObjectList.erase(StartIter);
			EndIter = LayerObjectList.end();
			continue;
		}
		//데이터상으론 존재한다. 하지만 보여주진않겠다!
		else if ((*StartIter)->GetisShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->Render(Hdc,DeltaTime);
		StartIter++;
	}
}

void Layer::AddObject(Object * pObj)
{
	pObj->SetScene(m_Scene);
	pObj->SetLayer(this);
	pObj->AddRefCount();

	LayerObjectList.push_back(pObj);
}

void Layer::EraseObject(Object * pObj)
{
	list<Object*>::iterator	iterStart = LayerObjectList.begin();
	list<Object*>::iterator	iterEnd = LayerObjectList.end();

	for (; iterStart != iterEnd; iterStart++ )
	{
		if (*iterStart == pObj)
		{
			SAFE_RELEASE((*iterStart));
			LayerObjectList.erase(iterStart);
			return;
		}
	}
}