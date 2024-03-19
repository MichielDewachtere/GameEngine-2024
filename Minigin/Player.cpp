#include "stdafx.h"
#include "Player.h"

#include "ColliderComponent.h"
#include "GameObject.h"

Player::Player(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

void Player::Start()
{
	m_Self = GetOwner()->GetComponent<dae::ColliderComponent>();
	healthChanged.Notify(m_Health);
	scoreChanged.Notify(m_Score);
}

// DISCLAIMER: Ugly test code
void Player::Update()
{
	if (m_MovePlayer)
	{
		GetOwner()->GetTransform()->Translate(-50, 0);
		m_MovePlayer = false;
	}

	if (m_Self->IsOverlapping(*m_pEnemy))
	{
		if (GetOwner()->GetTag() == "Pengo")
		{
			if (m_Health == 0)
				GetOwner()->Destroy();
			else
			{
				--m_Health;
				// Test code
				m_MovePlayer = true;
				healthChanged.Notify(m_Health);
			}
		}
		else if (GetOwner()->GetTag() == "Sno-Bee")
		{
			m_Score += 250;
			scoreChanged.Notify(m_Score);
		}
	}
}

void Player::AddScore(int score)
{
	if (GetOwner()->GetTag() != "Pengo")
		return;

	if (score < 0 && std::abs(score) > static_cast<int>(m_Score))
		m_Score = 0;
	else
		m_Score += score;

	scoreChanged.Notify(m_Score);
}

void Player::Damage()
{
	if (GetOwner()->GetTag() != "Sno-Bee")
		return;

	if (m_Health == 0)
		GetOwner()->Destroy();
	else
	{
		--m_Health;
		healthChanged.Notify(m_Health);
	}
}
