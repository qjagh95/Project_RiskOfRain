#include "../stdafx.h"
#include "SceneComponent.h"

SceneComponent::SceneComponent()
	:m_Scene(NULL)
{
}


SceneComponent::~SceneComponent()
{
}

int SceneComponent::Input(float DeltaTime)
{
	return 0;
}

int SceneComponent::Update(float DeltaTime)
{
	return 0;
}

int SceneComponent::LateUpdate(float DeltaTime)
{
	return 0;
}

void SceneComponent::Collision(float DeltaTime)
{
}

void SceneComponent::CollsionAfterUpdate(float DeltaTime)
{
}

void SceneComponent::Render(HDC hdc, float DeltaTime)
{
}
