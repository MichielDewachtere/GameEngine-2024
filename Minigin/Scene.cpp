#include "stdafx.h"
#include "Scene.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(std::string name)
	: m_Name(std::move(name))
{
	//if (SceneManager::GetInstance().HasScene(m_Name) == false)
	//	SceneManager::GetInstance().AddScene(m_Name);
}

Scene::~Scene() = default;

GameObject& Scene::CreateGameObject(std::string tag)
{
	auto pGameObject = std::make_unique<GameObject>(this, std::move(tag));
	m_GameObjects.emplace_back(std::move(pGameObject));
	return *m_GameObjects.back();
}

void Scene::AddGameObject(GameObject* pGo)
{
	m_GameObjects.emplace_back(std::unique_ptr<GameObject>(pGo));
}

void Scene::AddGameObject(std::unique_ptr<GameObject> pGo)
{
	m_GameObjects.emplace_back(std::move(pGo));
}

GameObject* Scene::GetGameObject(UINT id) const
{
	for (const auto& go : m_GameObjects)
	{
		if (go->GetId() == id)
			return go.get();

		if (const auto child = go->GetChild(id);
			child != nullptr)
			return child;
	}

	return nullptr;
}

std::unique_ptr<GameObject> Scene::GetUniqueGameObject(GameObject* pGo)
{
	for (auto it = m_GameObjects.begin(); it < m_GameObjects.end(); ++it)
	{
		if (it->get() != pGo)
			continue;

		auto pUnique{ std::move(*it) };
		m_GameObjects.erase(it);

		return pUnique;
	}

	return nullptr;
}

void Scene::Remove(GameObject* /*pGo*/)
{
	m_DeleteGameObject = true;
}

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
	std::ranges::for_each(m_GameObjects, [](const auto& go)
		{
			go->FixedUpdate();
		});
}

void Scene::Update()
{
	if (m_IsFirstFrame)
	{
		std::ranges::for_each(m_GameObjects, [](const auto& go)
			{
				go->Start();
			});
		m_IsFirstFrame = false;
	}

	std::ranges::for_each(m_GameObjects, [](const auto& go)
		{
			go->Update();
		});

	std::ranges::for_each(m_GameObjects, [](const auto& go)
		{
			go->LateUpdate();
		});

	if (m_DeleteGameObject)
	{
		for (auto it = m_GameObjects.begin(); it != m_GameObjects.end();)
		{
			if ((*it)->IsMarkedForDestroy())
			{
				it = m_GameObjects.erase(it);
			}
			else
				++it;
		}

		m_DeleteGameObject = false;
	}
}

void Scene::Render() const
{
	std::ranges::for_each(m_GameObjects, [](const auto& go)
		{
			go->Render();
		});
}