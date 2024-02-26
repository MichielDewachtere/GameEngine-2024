#include "stdafx.h"
#include "SceneManager.h"

#include "Scene.h"

dae::SceneManager::~SceneManager()/* = default;*/
{
	for (auto pScene : m_ScenePtrs)
	{
		if (pScene != nullptr)
		{
			delete pScene;
			pScene = nullptr;
		}
	}
}

dae::Scene& dae::SceneManager::CreateScene(std::string name)
{
	//auto pScene = std::make_unique<Scene>(name);
	auto pScene = new Scene(name);
	m_ScenePtrs.emplace_back(std::move(pScene));
	return *m_ScenePtrs.back();
}

void dae::SceneManager::FixedUpdate()
{
	for (const auto& scene : m_ScenePtrs)
	{
		scene->FixedUpdate();
	}
}

void dae::SceneManager::Update()
{
	for(const auto& scene : m_ScenePtrs)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_ScenePtrs)
	{
		scene->Render();
	}
}

void dae::SceneManager::Destroy()
{
	for (const auto& scene : m_ScenePtrs)
	{
		scene->Destroy();
	}
}

//dae::Scene& dae::SceneManager::AddScene(std::string name)
//{
//	m_CreatingScene = name;
//	auto pScene = std::make_unique<Scene>(name);
//	m_ScenePtrs.emplace_back(std::move(pScene));
//	return *m_ScenePtrs.back();
//}

//bool dae::SceneManager::HasScene(const std::string& name)
//{
//	if (m_CreatingScene == name)
//		return true;
//
//	const bool found = std::ranges::any_of(m_ScenePtrs, [&](const std::unique_ptr<Scene>& s)
//		{
//			return s->GetName() == name;
//		});
//
//	return found;
//}
