#include "stdafx.h"
#include "Rotator.h"

#include "GameObject.h"
#include "GameTime.h"

#include <numbers>

Rotator::Rotator(dae::GameObject* pOwner, glm::vec2 pivot, float rotationSpeed)
	: Component(pOwner)
	, m_Pivot(pivot)
	, m_RotationSpeed(rotationSpeed)
	, m_Rotation(0)
{
}

void Rotator::Start()
{
	if (const auto pParent = GetOwner()->GetParent();
		pParent != nullptr)
	{
		m_Pivot = pParent->GetTransform()->GetWorldPosition();
	}

	m_Distance = distance(m_Pivot, GetOwner()->GetTransform()->GetWorldPosition());
}

void Rotator::Update()
{
	// TODO: could be done in local space
	const auto pTransform = GetOwner()->GetTransform();

	if (pTransform == nullptr)
		return;

	if (const auto pParent = GetOwner()->GetParent();
		pParent != nullptr)
	{
		m_Pivot = pParent->GetTransform()->GetWorldPosition();
	}

	glm::vec2 newPos = m_Pivot;

	m_Rotation += m_RotationSpeed * dae::GameTime::GetInstance().GetElapsed();

	if (m_Rotation >= 360.f)
		m_Rotation = 0;

	newPos.x += m_Distance * glm::cos(m_Rotation);
	newPos.y += m_Distance * glm::sin(m_Rotation);

	pTransform->SetWorldPosition(newPos);
}