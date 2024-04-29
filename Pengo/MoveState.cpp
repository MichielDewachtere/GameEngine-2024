#include "MoveState.h"

#include <GameObject.h>
#include <random>
#include <SpriteComponent.h>
#include <SceneManager.h>

#include "Game.h"
#include "GameInfo.h"
#include "GameUtil.h"
#include "Move.h"
#include "Player.h"

MoveState::MoveState(real::GameObject* pOwner)
	: IEnemyState(pOwner)
{
}

void MoveState::Enter()
{
	m_pMoveComponent = GetOwner()->GetComponent<Move>();
	m_pMazeComponent = GetOwner()->GetParent()->GetComponent<Maze>();
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

	if (m_pMoveComponent->IsMoving() == false)
	{
		MoveEnemy();
	}

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

void MoveState::MoveEnemy()
{
	const int left = GetPoints(Direction::left);
	const int right = GetPoints(Direction::right) + left;
	const int up = GetPoints(Direction::up) + right;
	const int down = GetPoints(Direction::down) + up;

	[[maybe_unused]] const auto value = GetValue(down);

	if (value <= left)
		m_pMoveComponent->MoveInDirection(Direction::left);
	else if (value > left && value <= right)
		m_pMoveComponent->MoveInDirection(Direction::right);
	else if (value > right && value <= up)
		m_pMoveComponent->MoveInDirection(Direction::up);
	else if (value > up)
		m_pMoveComponent->MoveInDirection(Direction::down);
}

int MoveState::GetPoints(Direction direction)
{
	if (IsObstacle(direction))
		return 0;

	const auto currentDir = m_pMoveComponent->GetDirection();
	if (InvertDirection(currentDir) == direction)
	{
		if (IsIce(direction))
			return 0;

		return 1;
	}

	if (IsIce(direction))
		return 3;

	return 5;
}

bool MoveState::IsObstacle(Direction direction)
{
	const auto posToCheck = m_pMoveComponent->GetMazePos() + DirectionToVector(direction);
	auto type = m_pMazeComponent->GetBlock(posToCheck);
	if (type == Maze::BlockType::player || type == Maze::BlockType::air || type == Maze::BlockType::ice)
		return false;

	return true;
}

bool MoveState::IsIce(Direction direction)
{
	const auto posToCheck = m_pMoveComponent->GetMazePos() + DirectionToVector(direction);
	auto type = m_pMazeComponent->GetBlock(posToCheck);
	if (type == Maze::BlockType::ice)
		return true;

	return false;
}

int MoveState::GetValue(int max)
{
	// Seed the random number generator
	static std::random_device rd;
	static std::mt19937 gen(rd());

	// Define a distribution for the range [min_value, max_value]
	std::uniform_int_distribution dist(0, max);

	// Generate a random number
	return dist(gen);
}
