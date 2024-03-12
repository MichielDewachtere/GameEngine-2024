#include "stdafx.h"
#include "Transform.h"

#include "GameObject.h"

dae::Transform::Transform(GameObject* pOwner, glm::vec3 localPos)
	: Component(pOwner)
	, m_LocalPosition(localPos)
{
}

void dae::Transform::Start()
{
}

const glm::vec2& dae::Transform::GetLocalPosition()
{
	if (m_LocalNeedsUpdate)
	{
		m_LocalNeedsUpdate = false;

		if (GetOwner()->GetParent() == nullptr)
			m_LocalPosition = m_WorldPosition;
		else
			m_LocalPosition = GetOwner()->GetParent()->GetTransform()->GetWorldPosition() - m_WorldPosition;
	}

	return m_LocalPosition;
}

void dae::Transform::SetLocalPosition(const glm::vec2& localPos)
{
	m_LocalPosition = localPos;
	m_WorldNeedsUpdate = true;
}

void dae::Transform::SetLocalPosition(const float x, const float y)
{
	SetLocalPosition({ x,y });
}

const glm::vec2& dae::Transform::GetWorldPosition()
{
	if (m_WorldNeedsUpdate)
	{
		m_WorldNeedsUpdate = false;

		if (GetOwner()->GetParent() == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = GetOwner()->GetParent()->GetTransform()->GetWorldPosition() + m_LocalPosition;
	} 

	return m_WorldPosition;
}

void dae::Transform::SetWorldPosition(const glm::vec2& worldPos)
{
	m_WorldPosition = worldPos;
	m_LocalNeedsUpdate = true;
}

void dae::Transform::SetWorldPosition(const float x, const float y)
{
	SetWorldPosition({ x,y });
}

void dae::Transform::Translate(const glm::vec2& translation)
{
	m_LocalPosition += translation;
	m_WorldNeedsUpdate = true;
}

void dae::Transform::Translate(float translationX, float translationY)
{
	Translate({ translationX, translationY });
}

//void dae::Transform::SetRotation(float rotation)
//{
//	m_Rotation = rotation;
//}
//
//void dae::Transform::IncrementRotation(const float amount)
//{
//	m_Rotation += amount;
//}
//
//void dae::Transform::DecrementRotation(const float amount)
//{
//	m_Rotation -= amount;
//}