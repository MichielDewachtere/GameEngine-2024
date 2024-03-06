#include "stdafx.h"
#include "GameObject.h"

#include "DrawableComponent.h"
#include "SceneManager.h"

dae::GameObject::GameObject(Scene* scene, std::string tag)
	: m_Tag(std::move(tag))
	, m_pScene(scene)
{
	m_Id = m_IdCounter++;
	m_pTransform = std::make_unique<Transform>(this);
}

dae::GameObject& dae::GameObject::CreateGameObject(std::string tag)
{
	m_pChildrenToAdd.push_back(std::make_unique<GameObject>(m_pScene, std::move(tag)));
	m_pChildrenToAdd.back()->m_pParent = this;

	return *m_pChildrenToAdd.back();
}

void dae::GameObject::Start()
{
	if (IsActive() == false)
		return;

	m_pTransform->Start();
	std::ranges::for_each(m_pComponents, [](const std::unique_ptr<Component>& c)
		{
			c->Start();
		});

	if (m_pChildrenToAdd.empty() == false)
	{
		for (auto& pChild : m_pChildrenToAdd)
		{
			m_pChildren.push_back(std::move(pChild));
		}

		m_pChildrenToAdd.clear();
	}

	if (m_pChildren.empty() == false)
	{
		std::ranges::for_each(m_pChildren, [](const auto& go)
			{
				go->Start();
			});
	}
}

void dae::GameObject::FixedUpdate()
{
	if (IsActive() == false)
		return;

	m_pTransform->FixedUpdate();
	std::ranges::for_each(m_pComponents, [](const std::unique_ptr<Component>& c)
		{
			c->FixedUpdate();
		});

	if (m_pChildren.empty() == false)
	{
		std::ranges::for_each(m_pChildren, [](const auto& go)
			{
				go->FixedUpdate();
			});
	}
}

void dae::GameObject::Update()
{
	if (IsActive() == false)
		return;

	m_pTransform->Update();
	std::ranges::for_each(m_pComponents, [](const std::unique_ptr<Component>& c)
		{
			c->Update();
		});

	if (m_pChildren.empty() == false)
	{
		std::ranges::for_each(m_pChildren, [](const auto& go)
			{
				go->Update();
			});
	}
}

void dae::GameObject::LateUpdate()
{
	if (IsActive())
	{
		if (m_pChildren.empty() == false)
		{
			for (auto it = m_pChildren.begin(); it != m_pChildren.end(); )
			{
				const auto& pChild = *it;

				if (IsActive())
					pChild->LateUpdate();

				if (pChild->IsMarkedForDestroy() && pChild->GetId() <= m_IdCounter)
				{
					it = m_pChildren.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		m_pTransform->LateUpdate();
		std::ranges::for_each(m_pComponents, [](const std::unique_ptr<Component>& c)
			{
				c->LateUpdate();
			});
	}

	if (m_IsMarkedForDestroy)
	{
		m_pComponents.clear();

		if (m_pParent == nullptr)
			m_pScene->Remove(this);
	}
}

void dae::GameObject::Render() const
{
	if (IsActive() == false)
		return;

	std::ranges::for_each(m_pComponents, [](const std::unique_ptr<Component>& c)
			{
				if (const auto drawable = dynamic_cast<DrawableComponent*>(c.get());
					drawable != nullptr)
				{
					drawable->Render();
				}
			});

	if (m_pChildren.empty() == false)
	{
		std::ranges::for_each(m_pChildren, [](const auto& go)
		   {
			   go->Render();
		   });
	}
}

void dae::GameObject::Destroy()
{
	m_IsMarkedForDestroy = true;

	std::ranges::for_each(m_pChildren, [](const auto& go)
		{
			go->Destroy();
		});
}

void dae::GameObject::SetIsActive(bool isEnabled, bool applyToChildren)
{
	if (m_IsActive != isEnabled)
	{
		m_IsActive = isEnabled;

		if (applyToChildren)
		{
			std::ranges::for_each(m_pChildren, [&](const auto& c)
			   {
				   c->SetIsActive(isEnabled, applyToChildren);
			   });
		}
	}
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_pParent;
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	if (IsChild(pParent) || pParent == this || m_pParent == pParent)
	{
		if (pParent == nullptr)
			Logger::LogWarning({ "Couldn't attach game object ( id: {} ) as a child, passed parent game object was NULL" }, m_Id);
		else
			Logger::LogWarning({ "Couldn't attach game object ( id: {} ) as a child to game object ( id: {} )" }, m_Id, pParent->GetId());

		return;
	}

	if (m_pParent != nullptr)
	{
		for (int i = 0; i < static_cast<int>(m_pParent->m_pChildren.size()); ++i)
		{
			if (m_pParent->m_pChildren[i]->m_Id == m_Id)
			{
				// If pParent is nullptr, the scene should own the game object
				if (pParent == nullptr)
					m_pScene->AddGameObject(std::move(m_pParent->m_pChildren[i]));
				// else, the defined parent should own the game object
				else
					pParent->m_pChildren.push_back(std::move(m_pParent->m_pChildren[i]));

				// Remove the dangling pointer
				m_pParent->m_pChildren[i] = std::move(m_pParent->m_pChildren[m_pParent->m_pChildren.size() - 1]);
				m_pParent->m_pChildren.pop_back();

				// Set the current parent
				m_pParent = pParent;
				break;
			}
		}
	}
	else
	{
		m_pParent = pParent;
		// Move the game object from the scene to the new parent
		m_pParent->m_pChildren.push_back(std::move(m_pScene->GetUniqueGameObject(this)));
	}

	// Update the position
	if (keepWorldPosition && m_pParent != nullptr)
		m_pTransform->SetWorldPosition(m_pTransform->GetLocalPosition() + m_pParent->GetTransform()->GetWorldPosition());
	else
		m_pTransform->SetLocalPosition(m_pTransform->GetWorldPosition());
}

UINT dae::GameObject::GetChildCount() const
{
	return static_cast<UINT>(m_pChildren.size());
}

dae::GameObject* dae::GameObject::GetChildAt(UINT index) const
{
	return m_pChildren[index].get();
}

dae::GameObject* dae::GameObject::GetChild(UINT id) const
{
	for (const auto& child : m_pChildren)
	{
		if (child->GetId() == id)
			return child.get();


		if (const auto pGo = child->GetChild(id);
			pGo != nullptr)
			return pGo;
	}

	return nullptr;
}

bool dae::GameObject::IsChild(GameObject* pGo) const
{
	return std::ranges::any_of(m_pChildren, [pGo](const auto& pChild)
		{
			return pChild->GetId() == pGo->GetId();
		});
}
