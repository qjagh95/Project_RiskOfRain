#pragma once
#include "../RefCount.h"
class SceneComponent : public RefCount
{
public:
	friend class Scene;

	virtual bool Init() = 0;
	virtual int Input(float DeltaTime);
	virtual int Update(float DeltaTime);
	virtual int LateUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void Render(HDC hdc, float DeltaTime);

	void SetScene(Scene* Value) { m_Scene = Value; }
	Scene* GetScene() const { return m_Scene; }

protected:
	SceneComponent();
	virtual ~SceneComponent() = 0;

	Scene* m_Scene;
};

