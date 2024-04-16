#include "SpawnState.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "MoveState.h"

SpawnState::SpawnState(real::GameObject* pOwner)
	: IEnemyState(pOwner)
{
}

void SpawnState::Enter()
{
	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();
	m_pSpriteComponent->PlayAnimation(0, 5, 0);
}

IEnemyState* SpawnState::Update()
{
	if (m_pSpriteComponent->IsAnimationPlaying() == false)
	{
		m_pSpriteComponent->PlayAnimation(8, 9);

		const auto returnState = new MoveState(GetOwner());
		returnState->Enter();
		return returnState;
	}

	return nullptr;
}

void SpawnState::Exit()
{
	m_pSpriteComponent->Pause(true);
}
