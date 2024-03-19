#include "ColliderTest.h"

#include <GameObject.h>
#include <Logger.h>

ColliderTest::ColliderTest(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

void ColliderTest::Start()
{
	m_Self = GetOwner()->GetComponent<dae::ColliderComponent>();
}

void ColliderTest::Update()
{
	if (m_Self->IsEntirelyOverlapping(*m_pOther, {2,2}))
		dae::Logger::LogInfo({ "Game object {} is entirely overlapping with game object {}" }, GetOwner()->GetId(), m_pOther->GetOwner()->GetId());
	else if (m_Self->IsOverlapping(*m_pOther))
		dae::Logger::LogInfo({ "Game object {} is overlapping with game object {}" }, GetOwner()->GetId(), m_pOther->GetOwner()->GetId());
}

void ColliderTest::SetColliderToCheck(dae::ColliderComponent* pOther)
{
	m_pOther = pOther;
}
