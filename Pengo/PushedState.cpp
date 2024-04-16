#include "PushedState.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "DiedState.h"
#include "Move.h"
#include "Pushable.h"

std::map<Direction, std::pair<int, int>> PushedState::m_DirectionToSquashAnim{
	{Direction::up, {32,33}},
	{Direction::right, {34,35}},
	{Direction::down, {36,37}},
	{Direction::left, {38,39}}
};


PushedState::PushedState(real::GameObject* pOwner)
	: IEnemyState(pOwner)
{
}

void PushedState::Enter()
{
	m_pPushableComponent = GetOwner()->GetComponent<Pushable>();
	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();

	m_pPushableComponent->Push(m_PushDirection);
}

IEnemyState* PushedState::Update()
{
	if (m_pPushableComponent->IsBeingPushed())
	{
		m_pSpriteComponent->Pause(true);
	}
	else
	{
		if (m_pSpriteComponent->IsPaused())
		{
			m_pSpriteComponent->Pause(false);
			m_pSpriteComponent->PlayAnimation(m_DirectionToSquashAnim[m_PushDirection].first,
				m_DirectionToSquashAnim[m_PushDirection].second,
				0, 0.1f);
		}
		else if (m_pSpriteComponent->IsAnimationPlaying() == false)
		{
			m_pSpriteComponent->Disable();
			return new DiedState(GetOwner());
		}
	}

	return nullptr;
}

void PushedState::Exit()
{
	m_pSpriteComponent->Pause(true);
}
