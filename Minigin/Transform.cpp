#include "stdafx.h"
#include "Transform.h"

dae::Transform::Transform(GameObject* pOwner, glm::vec3 localPos)
	: Component(pOwner)
	, m_LocalPosition(localPos)
{
}

const glm::vec2& dae::Transform::GetLocalPosition()
{
	if (m_LocalNeedsUpdate)
	{
		m_LocalPosition = m_WorldPosition;
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
		m_WorldPosition = m_LocalPosition;
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
