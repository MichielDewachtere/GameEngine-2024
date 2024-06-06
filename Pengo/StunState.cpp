#include "StunState.h"

#include <GameObject.h>
#include <SpriteComponent.h>
#include <GameTime.h>
#include <SceneManager.h>
#include <ColliderComponent.h>

#include "DiedState.h"
#include "GameInfo.h"
#include "HUD.h"
#include "Locator.h"
#include "Move.h"
#include "MoveState.h"
#include "Player.h"
#include "ScoreDisplay.h"

StunState::StunState(real::GameObject* pOwner, bool controlledManually)
	: IEnemyState(pOwner)
	, m_ControlledManually(controlledManually)
{
}

void StunState::Enter()
{
	real::Locator::GetAudioSystem().Play(Sounds::sno_bee_stunned);

	GetOwner()->GetComponent<real::SpriteComponent>()->Pause(false);
	GetOwner()->GetComponent<real::SpriteComponent>()->PlayAnimation(6, 7);

	m_MazePos = GetOwner()->GetComponent<Move>()->GetMazePos();

	m_pColliderComponent = GetOwner()->GetComponent<real::ColliderComponent>();

	RegisterPlayers();
}

IEnemyState* StunState::Update()
{
	m_AccuTime += real::GameTime::GetInstance().GetElapsed();

	if (m_AccuTime > m_StunTime)
	{
		Exit();
		const auto returnState = new MoveState(GetOwner(), m_ControlledManually);
		returnState->Enter();
		return returnState;
	}

	for (const auto& player : m_Players)
	{
		if (m_pColliderComponent->IsEntirelyOverlapping(*player, { 3,3 }))
		//if (player->GetMazePos() == m_MazePos)
		{
			HUD::GetInstance().AddScore(ScoreEvents::stunKill, player->GetOwner()->GetComponent<Player>()->GetPlayerNumber());
			return new DiedState(GetOwner());
		}
	}

	return nullptr;
}

void StunState::Exit()
{
	GetOwner()->GetComponent<real::SpriteComponent>()->SelectSprite(8);
}

void StunState::RegisterPlayers()
{
	const auto v = real::SceneManager::GetInstance().GetActiveScene().FindGameObjectsWithTag(Tags::pengo);
	if (v.empty() == false)
	{
		std::ranges::for_each(v, [this](real::GameObject* go)
			{
				m_Players.push_back(go->GetComponent<real::ColliderComponent>());
				//m_Players.push_back(go->GetComponent<Move>());
			});
	}
}
