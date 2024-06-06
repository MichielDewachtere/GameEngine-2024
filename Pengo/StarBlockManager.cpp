#include "StarBlockManager.h"

#include <GameObject.h>
#include <ranges>
#include <SpriteComponent.h>

#include "Enemy.h"
#include "Game.h"
#include "HUD.h"
#include "Macros.h"
#include "Move.h"
#include "Player.h"
#include "PlayerManager.h"
#include "ScoreDisplay.h"
#include "Pushable.h"
#include "SceneManager.h"

StarBlockManager::StarBlockManager(real::GameObject* pOwner)
	: Component(pOwner)
{
}

StarBlockManager::~StarBlockManager() = default;

void StarBlockManager::Start()
{
	for (const auto& block : m_pStarBlocks | std::views::keys)
	{
		block->GetComponent<Move>()->moved.AddObserver(this);
	}
}

void StarBlockManager::Update()
{
	if (m_BonusAdded)
	{
		bool animationFinished = false;

		for (const auto& block : m_pStarBlocks | std::views::keys)
		{
			const auto spriteComponent = block->GetComponent<real::SpriteComponent>();
			if (animationFinished = !spriteComponent->IsAnimationPlaying(); animationFinished)
				spriteComponent->SelectSprite(9);
		}

		if (animationFinished)
		{
			GetOwner()->RemoveComponent<StarBlockManager>();
		}
	}
}

void StarBlockManager::Kill()
{
	RemoveObserver();
}

void StarBlockManager::HandleEvent(MoveEvents event, const glm::ivec2&)
{
	if (event == MoveEvents::moved)
	{
		GatherPositions();
		CheckAdjacentBlocks();
	}
}

void StarBlockManager::AddStarBlock(real::GameObject* go, const glm::ivec2& pos)
{
	for (auto& [block, blockPos] : m_pStarBlocks)
	{
		if (block == nullptr)
		{
			block = go;
			blockPos = pos;
			break;
		}
	}
}

void StarBlockManager::GatherPositions()
{
	for (auto& [block, pos] : m_pStarBlocks)
	{
		pos = block->GetComponent<Move>()->GetMazePos();
	}
}

void StarBlockManager::CheckAdjacentBlocks()
{
	m_AdjacentBlocks = 0;
	m_Orientation = Orientation::none;

	m_AdjacentBlocks += IsAdjacent(m_pStarBlocks[0].second, m_pStarBlocks[1].second);
	m_AdjacentBlocks += IsAdjacent(m_pStarBlocks[1].second, m_pStarBlocks[2].second);
	m_AdjacentBlocks += IsAdjacent(m_pStarBlocks[2].second, m_pStarBlocks[0].second);

	if (m_AdjacentBlocks == 1)
	{
		for (const auto& block : m_pStarBlocks | std::views::keys)
		{
			const auto spriteComponent = block->GetComponent<real::SpriteComponent>();
			spriteComponent->PlayAnimation({ 9,18 }, -1);
		}
	}
	else if (m_AdjacentBlocks == 2)
	{
		if (m_IsTouchingWall)
			AddScore(ScoreEvents::starBlockWall);
		else
			AddScore(ScoreEvents::starBlock);

		for (const auto& block : m_pStarBlocks | std::views::keys)
		{
			const auto spriteComponent = block->GetComponent<real::SpriteComponent>();
			spriteComponent->PlayAnimation(9, 17, 2);

			block->RemoveComponent<Pushable>();
		}

		for (const auto& go : real::SceneManager::GetInstance().GetActiveScene().FindGameObjectsWithTag("Enemy"))
		{
			if (const auto pEnemy = go->GetComponent<Enemy>())
				pEnemy->Stun();
		}

		m_BonusAdded = true;

		RemoveObserver();
	}
	else
	{
		for (const auto& block : m_pStarBlocks | std::views::keys)
		{
			const auto spriteComponent = block->GetComponent<real::SpriteComponent>();
			spriteComponent->SelectSprite(9);
		}
	}
}

bool StarBlockManager::IsAdjacent(const glm::ivec2& pos1, const glm::ivec2& pos2)
{
	m_IsTouchingWall = IsTouchingWall(pos1);
	m_IsTouchingWall = IsTouchingWall(pos2);

	// Check if pos2 is adjacent to pos1 horizontally or vertically
	if ((pos1.x == pos2.x + 1 || pos1.x == pos2.x - 1) && pos1.y == pos2.y
		&& (m_Orientation == Orientation::none || m_Orientation == Orientation::horizontal))
	{
		if (m_Orientation == Orientation::none)
			m_Orientation = Orientation::horizontal;

		return true;
	}

	if ((pos1.y == pos2.y + 1 || pos1.y == pos2.y - 1) && pos1.x == pos2.x
		&& (m_Orientation == Orientation::none || m_Orientation == Orientation::vertical))
	{
		if (m_Orientation == Orientation::none)
			m_Orientation = Orientation::vertical;
		return true;
	}

	return false;
}

bool StarBlockManager::IsTouchingWall(const glm::ivec2& pos) const
{
	if (m_IsTouchingWall)
		return true;

	return pos.x == 0 || pos.x == MAZE_WIDTH - 1 || pos.y == 0 || pos.y == MAZE_HEIGHT - 1;
}

void StarBlockManager::RemoveObserver()
{
	for (const auto& block : m_pStarBlocks | std::views::keys)
	{
		if (const auto move = block->GetComponent<Move>())
		{
			move->moved.RemoveObserver(this);
		}
	}
}

void StarBlockManager::AddScore(ScoreEvents score)
{
	HUD::GetInstance().AddScore(score, PlayerNumber::playerOne);
	if (PlayerManager::GetInstance().GetAmountOfPlayers() == 2 && Game::GetIsPvP() == false)
	{
		HUD::GetInstance().AddScore(score, PlayerNumber::playerTwo);
	}

}
