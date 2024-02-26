#include "stdafx.h"
#include "GameObject.h"

#include "DrawableComponent.h"

dae::GameObject::GameObject(std::string tag)
	: m_Tag(std::move(tag))
{
	m_Id = m_IdCounter++;
	m_pTransform = std::make_unique<Transform>(this);
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start()
{
	if (IsEnabled() == false)
		return;

	m_pTransform->Start();
	std::ranges::for_each(m_ComponentPtrs, [](const std::unique_ptr<Component>& c)
		{
			c->Start();
		});
}

void dae::GameObject::FixedUpdate()
{
	if (IsEnabled() == false)
		return;

	m_pTransform->FixedUpdate();
	std::ranges::for_each(m_ComponentPtrs, [](const std::unique_ptr<Component>& c)
		{
			c->FixedUpdate();
		});
}

void dae::GameObject::Update()
{
	if (IsEnabled() == false)
		return;

	m_pTransform->Update();
	std::ranges::for_each(m_ComponentPtrs, [](const std::unique_ptr<Component>& c)
		{
			c->Update();
		});
}

void dae::GameObject::LateUpdate()
{
	if (IsEnabled() == false)
		return;

	m_pTransform->LateUpdate();
	std::ranges::for_each(m_ComponentPtrs, [](const std::unique_ptr<Component>& c)
		{
			c->LateUpdate();
		});

	// TODO: Destroy
	//if (m_IsMarkedForDestroy)
	//{
	//	Destroy all components
	//}
}

void dae::GameObject::Render() const
{
	std::ranges::for_each(m_ComponentPtrs, [](const std::unique_ptr<Component>& c)
		{
			if (const auto drawable = dynamic_cast<DrawableComponent*>(c.get());
				drawable != nullptr)
			{
				drawable->Render();
			}
		});
}

void dae::GameObject::Destroy()
{
	m_IsMarkedForDestroy = true;
}
