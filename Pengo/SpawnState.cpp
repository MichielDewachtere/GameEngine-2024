#include "SpawnState.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "Game.h"
#include "MoveState.h"

SpawnState::SpawnState(real::GameObject* pOwner, bool deSpawn)
	: IEnemyState(pOwner)
	, m_DeSpawn(deSpawn)
{
}

void SpawnState::Enter()
{
	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();

	if (m_DeSpawn == false)
		m_pSpriteComponent->PlayAnimation(0, 5, 0);
	else
		m_pSpriteComponent->PlayAnimation({ 5,4,3,2,1,0 }, 0);
}

IEnemyState* SpawnState::Update()
{
	if (m_pSpriteComponent->IsAnimationPlaying() == false)
	{
		if (m_DeSpawn == false)
		{
			const auto returnState = new MoveState(GetOwner());
			returnState->Enter();
			return returnState;
		}

		//GetOwner()->GetParent()->GetComponent<Game>()->EndAct(true);
	}


	return nullptr;
}

void SpawnState::Exit()
{
	m_pSpriteComponent->Pause(true);
}
