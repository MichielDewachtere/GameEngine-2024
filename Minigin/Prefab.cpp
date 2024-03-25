#include "Prefab.h"

#include "GameObject.h"
#include "Scene.h"

dae::Prefab::Prefab(GameObject* pOwner)
{
	m_pGameObject = &pOwner->CreateGameObject();
}

dae::Prefab::Prefab(Scene* pScene)
{
	m_pGameObject = &pScene->CreateGameObject();
}
