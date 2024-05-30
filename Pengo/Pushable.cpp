#include "Pushable.h"

#include <GameObject.h>
#include <ColliderComponent.h>

#include "Enemy.h"
#include "Game.h"
#include "GameUtil.h"
#include "HUD.h"
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
			m_Pushed = false;

		if (m_pMoveComponent->GetType() != Maze::BlockType::ice)
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

	for (int i = 1; i <= 2; ++i)
	{
		const auto mazePos = m_pMoveComponent->GetMazePos();
		const auto secondPosToCheck = mazePos + i * DirectionToVector(m_Direction);
		auto [type, go] = m_pMazeComponent->GetBlockAndObject(secondPosToCheck);

		if (type != Maze::BlockType::enemy)
			continue;

		for (const auto& enemy : go)
		{
			if (std::ranges::find(m_EnemiesToPush, enemy) != m_EnemiesToPush.end()
				|| enemy->IsMarkedForDestroy())
				continue;

			m_EnemiesToPush.push_back(enemy);
		}
	}
}

void Pushable::PushEnemies()
{
	for (const auto& e : m_EnemiesToPush)
	{
		if (std::ranges::find(m_EnemiesPushed, e) != m_EnemiesPushed.end())
			continue;

		const auto colliderComp = e->GetComponent<real::ColliderComponent>();
		if (m_pColliderComponent->IsOverlapping(*colliderComp))
		{
			std::cout << "is overlapping\n";
			e->GetComponent<Move>()->Reset();
			//if (Game::GetIsPvP())
			//	//e->GetComponent<Player>()->Push(m_Direction);
			//else
				e->GetComponent<Enemy>()->Push(m_Direction); 
			m_EnemiesPushed.push_back(e);
		}
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
