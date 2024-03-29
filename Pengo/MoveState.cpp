#include "MoveState.h"

#include <GameObject.h>
#include <SpriteComponent.h>
#include <SceneManager.h>

#include "Game.h"
#include "GameInfo.h"
#include "Move.h"

MoveState::MoveState(dae::GameObject* pOwner)
	: IEnemyState(pOwner)
{
}

void MoveState::Enter()
{
	m_pMoveComponent = GetOwner()->GetComponent<Move>();
	m_pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();
	m_pSpriteComponent->PlayAnimation(8, 9);

	RegisterPlayers();
}

IEnemyState* MoveState::Update()
{
	const auto mazePos = m_pMoveComponent->GetMazePos();

	for (auto it = m_Players.begin(); it != m_Players.end();)
	{
		if ((*it)->GetMazePos() == mazePos)
			it = m_Players.erase(it);
		else
			++it;
	}

	if (m_Players.empty())
		GetOwner()->GetParent()->GetComponent<Game>()->EndGame(false);

	return nullptr;
}

void MoveState::Exit()
{
	m_pSpriteComponent->Pause(true);
}

void MoveState::RegisterPlayers()
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
