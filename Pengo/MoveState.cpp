#include "MoveState.h"

#include <GameObject.h>
#include <SpriteComponent.h>
#include <SceneManager.h>

#include "Game.h"
#include "GameInfo.h"
#include "Move.h"
#include "Player.h"

MoveState::MoveState(real::GameObject* pOwner)
	: IEnemyState(pOwner)
{
}

void MoveState::Enter()
{
	m_pMoveComponent = GetOwner()->GetComponent<Move>();
	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();
	m_pSpriteComponent->PlayAnimation(8, 9);

	m_Players.clear();
	RegisterPlayers();
}

IEnemyState* MoveState::Update()
{
	const auto mazePos = m_pMoveComponent->GetMazePos();

	for (auto it = m_Players.begin(); it != m_Players.end();)
	{
		if ((*it).second->GetMazePos() == mazePos)
		{
			(*it).second->GetOwner()->GetComponent<Player>()->Die();
			it = m_Players.erase(it);
		}
		else
			++it;
	}

	if (m_Players.empty())
		GetOwner()->GetParent()->GetComponent<Game>()->EndAct(false);

	return nullptr;
}

void MoveState::Exit()
{
	m_pSpriteComponent->Pause(true);
}

void MoveState::RegisterPlayers() const
{
	const auto v = real::SceneManager::GetInstance().GetActiveScene().FindGameObjectsWithTag(Tags::pengo);
	if (v.empty() == false)
	{
		std::ranges::for_each(v, [this](real::GameObject* go)
			{
				m_Players.try_emplace(go->GetId(), go->GetComponent<Move>());
			});
	}
}
