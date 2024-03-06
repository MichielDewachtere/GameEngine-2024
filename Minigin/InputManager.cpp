#include "stdafx.h"
#include "InputManager.h"

#include "GameObject.h"
#include "imgui_impl_sdl2.h"
#include "SceneManager.h"

void dae::InputManager::Init()
{
}

bool dae::InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			if (e.key.keysym.scancode == SDL_SCANCODE_1)
			{
				const auto pChild = SceneManager::GetInstance().GetActiveScene().GetGameObject(m_ChildId);
				if (pChild == nullptr)
				{
					Logger::LogInfo({ "Child Object no longer exists" });
					return true;
				}
					
				// DETACH CHILD
				pChild->SetParent(nullptr, true);
				Logger::LogInfo({ "Detached child ( id: {} ) from parent ( id: {} )" }, m_ParentId, m_ChildId);
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_2)
			{
				const auto pChild = SceneManager::GetInstance().GetActiveScene().GetGameObject(m_ChildId);
				if (pChild == nullptr)
				{
					Logger::LogInfo({ "Child Object no longer exists" });
					return true;
				}
				const auto pParent = SceneManager::GetInstance().GetActiveScene().GetGameObject(m_ParentId);
				if (pParent == nullptr)
				{
					Logger::LogInfo({ "Parent Object no longer exists" });
					return true;
				}

				// ATTACH CHILD
				pChild->SetParent(pParent, true);
				Logger::LogInfo({ "Attached child ( id: {} ) to parent ( id: {} )" }, m_ChildId, m_ParentId);
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_3)
			{
				const auto pChild = SceneManager::GetInstance().GetActiveScene().GetGameObject(m_ChildId);
				if (pChild == nullptr)
				{
					Logger::LogInfo({ "Child Object no longer exists" });
					return true;
				}

				// DESTROY CHILD
				pChild->Destroy();
				Logger::LogInfo({ "Destroyed child ( id: {} )" }, pChild->GetId());
			}
			if (e.key.keysym.scancode == SDL_SCANCODE_4)
			{
				const auto pParent = SceneManager::GetInstance().GetActiveScene().GetGameObject(m_ParentId);
				if (pParent == nullptr)
				{
					Logger::LogInfo({ "Parent Object no longer exists" });
					return true;
				}

				// DESTROY PARENT
				pParent->Destroy();
				Logger::LogInfo({ "Destroyed parent ( id: {} )" }, pParent->GetId());
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			
		}
		// etc...
	}

	return true;
}
