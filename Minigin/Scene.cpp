#include "stdafx.h"
#include "Scene.h"

//#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(std::string name)
	: m_Name(std::move(name))
{
	//if (SceneManager::GetInstance().HasScene(m_Name) == false)
	//	SceneManager::GetInstance().AddScene(m_Name);
}

Scene::~Scene() = default;

GameObject& Scene::CreateGameObject()
{
	auto pGameObject = std::make_unique<GameObject>();
	m_GameObjects.emplace_back(std::move(pGameObject));
	return *m_GameObjects.back();
}

//void Scene::Remove(std::shared_ptr<GameObject> object)
//{
//	std::erase(m_GameObjects, object);
//}

void Scene::RemoveAll()
{
	m_GameObjects.clear();
}

void Scene::Destroy()
{
	for (const auto& object : m_GameObjects)
	{
		object->Destroy();
	}
}

void Scene::FixedUpdate()
{
	for (const auto& object : m_GameObjects)
	{
		object->FixedUpdate();
	}
}

void Scene::Update()
{
	for (const auto& object : m_GameObjects)
	{
		object->Update();
	}

	for(const auto& object : m_GameObjects)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_GameObjects)
	{
		object->Render();
	}
}