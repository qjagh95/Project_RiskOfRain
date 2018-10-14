#pragma once
#include "../RefCount.h"
class Layer;
class SceneComponent;
class Scene : public RefCount
{
public:
	friend class SceneManager;

	bool Init();
	int Input(float DeltaTime);
	int Update(float DeltaTime);
	int LateUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void Render(HDC Hdc, float DeltaTime);

	Layer* CreateLayer(const string& TagName, int ZOrder);
	Layer* FindLayer(const string& TagName);
	int GetObjectCount() const { return AllObjectCount; }

	template<typename T>
	T* CreateSceneComponent(const string& TagName)
	{
		T* newComponent = new T();

		newComponent->SetTag(TagName);
		newComponent->SetScene(this);

		if (newComponent->Init() == false)
		{
			SAFE_RELEASE(newComponent);
			return NULL;
		}
		newComponent->AddRefCount();
		m_SceneComponent = newComponent;

		return newComponent;
	}

private:
	Scene();
	~Scene();
	static bool LayerSort(Layer* Src, Layer *Dest);

	SceneComponent* m_SceneComponent; ///SceneComponent
	list<Layer*> LayerList;			  ///레이어 리스트
	int AllObjectCount;
};

