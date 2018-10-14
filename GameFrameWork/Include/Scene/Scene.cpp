#include "../stdafx.h"
#include "Scene.h"
#include "SceneComponent.h"
#include "Layer.h"
#include "../Object/Object.h"

bool Scene::LayerSort(Layer * Src, Layer *Dest)
{
	//true냐 false냐에따라서 오름차순 내림차순이 결정된다.
	return Src->Zorder < Dest->Zorder;
}

Scene::Scene()
	:m_SceneComponent(NULL), AllObjectCount(0)
{
}
Scene::~Scene()
{
	Object::EraseSceneObject(this);
	Object::EraseFindList();
	Object::ErasePrototype(this);
	SAFE_RELEASE(m_SceneComponent);
	Safe_Release_VecList(LayerList);
}

bool Scene::Init()
{
	Layer* newLayer = CreateLayer("BackGround", INT_MIN);

	SAFE_RELEASE(newLayer);

	newLayer = CreateLayer("TileLayer", 0);

	SAFE_RELEASE(newLayer);

	newLayer = CreateLayer("Default", 1);

	SAFE_RELEASE(newLayer);

	newLayer = CreateLayer("PlayLayer", 2);

	SAFE_RELEASE(newLayer);

	newLayer = CreateLayer("UI", INT_MAX);

	SAFE_RELEASE(newLayer);

	return true;
}

int Scene::Input(float DeltaTime)
{
	AllObjectCount = 0;
	m_SceneComponent->Input(DeltaTime);

	list<Layer*>::iterator StartIter = LayerList.begin();
	list<Layer*>::iterator EndIter = LayerList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			SAFE_RELEASE((*StartIter));
			StartIter = LayerList.erase(StartIter);
			EndIter = LayerList.end();
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

int Scene::Update(float DeltaTime)
{
	m_SceneComponent->Update(DeltaTime);

	list<Layer*>::iterator StartIter = LayerList.begin();
	list<Layer*>::iterator EndIter = LayerList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			SAFE_RELEASE((*StartIter));
			StartIter = LayerList.erase(StartIter);
			EndIter = LayerList.end();
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

int Scene::LateUpdate(float DeltaTime)
{
	m_SceneComponent->LateUpdate(DeltaTime);

	list<Layer*>::iterator StartIter = LayerList.begin();
	list<Layer*>::iterator EndIter = LayerList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			SAFE_RELEASE((*StartIter));
			StartIter = LayerList.erase(StartIter);
			EndIter = LayerList.end();
			continue;
		}
		//데이터상으론 존재한다. 하지만 보여주진않겠다!
		else if ((*StartIter)->GetisShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->LateUpdate(DeltaTime);
		AllObjectCount += (int)((*StartIter)->LayerObjectList.size());
		StartIter++;
	}
	return 0;
}

void Scene::Collision(float DeltaTime)
{
	m_SceneComponent->Collision(DeltaTime);

	list<Layer*>::iterator StartIter = LayerList.begin();
	list<Layer*>::iterator EndIter = LayerList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			SAFE_RELEASE((*StartIter));
			StartIter = LayerList.erase(StartIter);
			EndIter = LayerList.end();
			continue;
		}
		//데이터상으론 존재한다. 하지만 보여주진않겠다!
		else if ((*StartIter)->GetisShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->Collision(DeltaTime);
		StartIter++;
	}

}

void Scene::Render(HDC Hdc, float DeltaTime)
{
	m_SceneComponent->Render(Hdc,DeltaTime);

	list<Layer*>::iterator StartIter = LayerList.begin();
	list<Layer*>::iterator EndIter = LayerList.end();

	for (; StartIter != EndIter;)
	{
		if ((*StartIter)->GetisActiv() == false)
		{
			SAFE_RELEASE((*StartIter));
			StartIter = LayerList.erase(StartIter);
			EndIter = LayerList.end();
			continue;
		}
		//데이터상으론 존재한다. 하지만 보여주진않겠다!
		else if ((*StartIter)->GetisShow() == false)
		{
			StartIter++;
			continue;
		}

		(*StartIter)->Render(Hdc, DeltaTime);
		StartIter++;
	}
}

Layer * Scene::CreateLayer(const string & TagName, int ZOrder)
{
	Layer* newLayer = new Layer();

	newLayer->SetScene(this);
	newLayer->SetTag(TagName);
	newLayer->SetZOrder(ZOrder);

	if (newLayer->Init() == false)
	{
		SAFE_RELEASE(newLayer);
		return NULL;
	}

	newLayer->AddRefCount();
	LayerList.push_back(newLayer);

	//여기서 레이어가 2개이상 추가되었을 경우 정렬한다.
	if (LayerList.size() >= 2)
		LayerList.sort(Scene::LayerSort);

	return newLayer;
}

Layer * Scene::FindLayer(const string & TagName)
{
	list<Layer*>::iterator StartIter = LayerList.begin();
	list<Layer*>::iterator EndIter = LayerList.end();

	for (; StartIter != EndIter ; StartIter++)
	{
		if ((*StartIter)->GetTag() == TagName)
		{
			(*StartIter)->AddRefCount();
			return (*StartIter);
		}
	}
	return NULL;
}

