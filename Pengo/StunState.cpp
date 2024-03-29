#include "StunState.h"

#include <GameObject.h>
#include <SpriteComponent.h>
#include <GameTime.h>
#include <SceneManager.h>

#include "DiedState.h"
#include "GameInfo.h"
#include "Move.h"
#include "MoveState.h"

StunState::StunState(dae::GameObject* pOwner)
	: IEnemyState(pOwner)
{
}

void StunState::Enter()
{
	GetOwner()->GetComponent<dae::SpriteComponent>()->PlayAnimation(6, 7, 10, .5f);

	m_MazePos = GetOwner()->GetComponent<Move>()->GetMazePos();

	RegisterPlayers();
}

IEnemyState* StunState::Update()
{
	m_AccuTime += dae::GameTime::GetInstance().GetElapsed();

	if (m_AccuTime > m_StunTime)
	{
		Exit();
		const auto returnState = new MoveState(GetOwner());
		returnState->Enter();
		return returnState;
	}

	for (const auto & player : m_Players)
	{
		if (player->GetMazePos() == m_MazePos)
		{
			// TODO: Add Points
			std::cout << "+100\n";
			return new DiedState(GetOwner());
		}
	}

	return nullptr;
}

void StunState::Exit()
{
	GetOwner()->GetComponent<dae::SpriteComponent>()->SelectSprite(8);
}

void StunState::RegisterPlayers()
{
	const auto v = dae::SceneManager::GetInstance().GetActiveScene().FindGameObjectsWithTag(Tags::pengo);
	if (v.empty() == false)
	{
		std::ranges::for_each(v, [this](dae::GameObject* go)
			{
				m_Players.push_back(go->GetComponent<Move>());
			});
	}
}
