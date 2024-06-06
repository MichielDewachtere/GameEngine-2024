#include "Pushable.h"

#include <GameObject.h>
#include <ColliderComponent.h>
#include <Utils.h>

#include "Enemy.h"
#include "EnemyPlayer.h"
#include "Game.h"
#include "GameInfo.h"
#include "GameUtil.h"
#include "HUD.h"
#include "Locator.h"
#include "Move.h"
#include "Maze.h"
#include "ScoreDisplay.h"
#include "Macros.h"

std::map<Direction, glm::ivec2> Pushable::m_DirectionToOffset{
	{Direction::left, {-1,0}},
	{Direction::right, {BLOCK_SIZE * PIXEL_SCALE + 1,0}},
	{Direction::up, {0,-1}},
	{Direction::down, {0,BLOCK_SIZE * PIXEL_SCALE + 1}}
};

Pushable::Pushable(real::GameObject* pOwner)
	: Component(pOwner)
{
}

void Pushable::Start()
{
	m_pMoveComponent = GetOwner()->GetComponent<Move>();
	m_pMazeComponent = GetOwner()->GetParent()->GetComponent<Maze>();
	m_pColliderComponent = GetOwner()->GetComponent<real::ColliderComponent>();
}

void Pushable::Update()
{
	if (m_Pushed)
	{
		if (m_pMoveComponent->IsMoving() == false)
		{
			if (m_pMoveComponent->GetType() == Maze::BlockType::ice
				|| m_pMoveComponent->GetType() == Maze::BlockType::egg
				|| m_pMoveComponent->GetType() == Maze::BlockType::star)
				real::Locator::GetAudioSystem().Play(Sounds::block_stopped);

			m_Pushed = false;
		}

		if (m_pMoveComponent->GetType() != Maze::BlockType::ice
			&& m_pMoveComponent->GetType() != Maze::BlockType::egg
			&& m_pMoveComponent->GetType() != Maze::BlockType::star)
		return;

		LookForEnemies();
		PushEnemies();
	}
	else if (m_EnemiesPushed.empty() == false)
		AddPoints();
	else if (m_EnemiesToPush.empty() == false)
		m_EnemiesToPush.clear();
}

void Pushable::Push(Direction direction, PlayerNumber pushedBy)
{
	m_pMoveComponent->MoveInDirection(direction, true);
	m_Pushed = true;
	m_Direction = direction;
	m_PushedBy = pushedBy;
}

bool Pushable::IsBeingPushed() const
{
	return m_Pushed;
}

void Pushable::LookForEnemies()
{
	if (m_pMazeComponent->GetBlock(m_pMoveComponent->GetMazePos()) == Maze::BlockType::enemy
		|| m_pMazeComponent->GetBlock(m_pMoveComponent->GetMazePos()) == Maze::BlockType::air)
		return;

	// Fetch all the enemies in a 2x3 rectangle in front of the ice block
	const auto dirVec = DirectionToVector(m_Direction);
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = 1; j <= 2; ++j)
		{
			const auto mazePos = m_pMoveComponent->GetMazePos();
			const auto secondPosToCheck = mazePos + j * dirVec + i * glm::ivec2(std::abs(dirVec.y), std::abs(dirVec.x));
			auto [type, go] = m_pMazeComponent->GetBlockAndObject(secondPosToCheck);

			if (type != Maze::BlockType::enemy)
				continue;

			for (const auto& enemy : go)
			{
				if (std::ranges::find(m_EnemiesToPush, enemy) != m_EnemiesToPush.end()
					|| std::ranges::find(m_EnemiesPushed, enemy) != m_EnemiesPushed.end()
					|| enemy->IsMarkedForDestroy())
						continue;

				m_EnemiesToPush.push_back(enemy);
			}
		}
	}
}

void Pushable::PushEnemies()
{
	const auto tempCol = GenerateTempColliderComponent();

	//for (const auto& e : m_EnemiesToPush)
	for (auto it = m_EnemiesToPush.begin(); it != m_EnemiesToPush.end(); )
	{
		const auto e = (*it);

		const auto colliderComp = e->GetComponent<real::ColliderComponent>();
		if (tempCol->IsEntirelyOverlapping(*colliderComp, { 1,1 }))
		{
			e->GetComponent<Move>()->Reset();
			if (Game::GetIsPvP())
				e->GetComponent<EnemyPlayer>()->Push(m_Direction);
			else
				e->GetComponent<Enemy>()->Push(m_Direction);

			it = m_EnemiesToPush.erase(it);
			m_EnemiesPushed.push_back(e);
		}
		else 
			++it;
	}
}

void Pushable::AddPoints()
{
	switch (m_EnemiesPushed.size())
	{
	case 1:
		HUD::GetInstance().AddScore(ScoreEvents::kill, m_PushedBy);
		break;
	case 2:
		HUD::GetInstance().AddScore(ScoreEvents::doubleKill, m_PushedBy);
		break;
	case 3:
		HUD::GetInstance().AddScore(ScoreEvents::tripleKill, m_PushedBy);
		break;
	case 4:
		HUD::GetInstance().AddScore(ScoreEvents::quadKill, m_PushedBy);
		break;
	}

	enemiesCrushed.Notify(static_cast<int>(m_EnemiesPushed.size()));

	m_EnemiesPushed.clear();
}

real::ColliderComponent* Pushable::GenerateTempColliderComponent() const
{
	const auto dirVec = DirectionToVector(m_Direction);
	constexpr int blockSize = BLOCK_SIZE * PIXEL_SCALE;
	constexpr int halfBlockSize = blockSize / 2;

	const auto blockPos = glm::vec2(GetOwner()->GetTransform()->GetWorldPosition());

	const glm::vec2 tempColPos{
	blockPos.x + (dirVec.x == 0 ? -halfBlockSize : dirVec.x == 1 ? halfBlockSize : -blockSize),
	blockPos.y + (dirVec.y == 0 ? -halfBlockSize : dirVec.y == 1 ? halfBlockSize : -blockSize)
	};

	constexpr int height = blockSize * 2;
	constexpr int width = blockSize + halfBlockSize;
	const glm::vec2 tempColSize{
		dirVec.x != 0 ? width : height,
		dirVec.y != 0 ? width : height
	};

	const auto tempCol = new real::ColliderComponent(nullptr, real::ColliderInfo{ tempColPos, tempColSize });
	return tempCol;
}
