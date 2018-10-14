#pragma once
#include "../RefCount.h"
class Object;
class Layer : public RefCount
{
public:
	friend class Scene;

	bool Init();
	int Input(float DeltaTime);
	int Update(float DeltaTime);
	int LateUpdate(float DeltaTime);
	void Collision(float DeltaTime);
	void CollsionAfterUpdate(float DeltaTime);
	void Render(HDC Hdc, float DeltaTime);

	void SetScene(Scene* Value) { m_Scene = Value; }
	Scene* GetScene() const { return m_Scene; }
	void SetZOrder(int Value) { Zorder = Value; }
	void AddObject(Object* pObj);
	void EraseObject(Object *pObj);

private:
	Layer();
	~Layer();

	Scene* m_Scene;
	int Zorder;
	list<Object*> LayerObjectList;
};

