#include "MoveState.h"

#include <GameObject.h>
#include <random>
#include <SpriteComponent.h>
#include <SceneManager.h>

#include "Game.h"
#include "GameInfo.h"
#include "GameUtil.h"
#include "IceBreakState.h"
#include "Locator.h"
#include "Move.h"
#include "Player.h"
#include "PlayerManager.h"

MoveState::MoveState(real::GameObject* pOwner, bool controlledManually)
	: IEnemyState(pOwner)
	, m_ControlledManually(controlledManually)
{
}

void MoveState::Enter()
{
	m_pMoveComponent = GetOwner()->GetComponent<Move>();
	m_pMoveComponent->Animate(true);
	m_pMazeComponent = GetOwner()->GetParent()->GetComponent<Maze>();
	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();
	m_pSpriteComponent->Pause(false);
	//m_pSpriteComponent->PlayAnimation(8, 9);

	m_Players.clear();
	RegisterPlayers();
}

IEnemyState* MoveState::Update()
{
	CheckForPlayer();

	if (m_ControlledManually)
		return nullptr;

	if (m_pMoveComponent->IsMoving() == false)
	{
		MoveEnemy();
	}

	if (Game::GetGameTime() > 30)
	{
		real::Locator::GetAudioSystem().Stop(Sounds::popcorn_fast.channel);
		real::Locator::GetAudioSystem().Play(Sounds::popcorn_fast);

		return new IceBreakState(GetOwner());
	}

	return nullptr;
}

void MoveState::Exit()
{
	m_pSpriteComponent->Pause(true);
	m_pMoveComponent->Animate(false);
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

void MoveState::CheckForPlayer() const
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
}

void MoveState::MoveEnemy() const
{
	std::vector<Direction> directions;
	GetPoints(Direction::left, directions, true);
	GetPoints(Direction::right, directions, true);
	GetPoints(Direction::up, directions, true);
	GetPoints(Direction::down, directions, true);

	std::random_device rd;
	std::mt19937 g(rd());
	std::ranges::shuffle(directions, g);

	if (directions.empty())
		m_pMoveComponent->MoveInDirection(/*InvertDirection(*/m_pMoveComponent->GetDirection()/*)*/);
	else
		m_pMoveComponent->MoveInDirection(directions.front());
}

bool MoveState::GetPoints(Direction direction, std::vector<Direction>& v, bool ignoreIce) const
{
	bool isIce = false;
	if (auto [type, value] = IsObstacle(direction, ignoreIce); value)
	{
		if (ignoreIce == false && type == Maze::BlockType::ice)
			isIce = true;
		else
			return isIce;
	}

	const auto currentDir = m_pMoveComponent->GetDirection();
	if (InvertDirection(currentDir) == direction)
	{
		v.insert(v.end(), 1, direction);
		return isIce;
	}

	if (direction == currentDir)
	{
		if (isIce)
			v.insert(v.end(), 10, direction);
		else
			v.insert(v.end(), 16, direction);

		return isIce;
	}

		if (isIce)
			v.insert(v.end(), 5, direction);
		else
			v.insert(v.end(), 9, direction);

	return isIce;
}

std::pair<Maze::BlockType, bool> MoveState::IsObstacle(Direction direction, bool ignoreIce) const
{
	const auto posToCheck = m_pMoveComponent->GetMazePos() + DirectionToVector(direction);
	const auto type = m_pMazeComponent->GetBlock(posToCheck);

	if (ignoreIce && (type == Maze::BlockType::player || type == Maze::BlockType::air))
		return { type,false };

	if (!ignoreIce && (type == Maze::BlockType::player || type == Maze::BlockType::air || type == Maze::BlockType::ice))
	{
		if (type == Maze::BlockType::ice)
			return { type,true };

		return { type,false };
	}

	return { type, true };
}

//bool MoveState::IsIce(Direction direction) const
//{
//	const auto posToCheck = m_pMoveComponent->GetMazePos() + DirectionToVector(direction);
//	auto type = m_pMazeComponent->GetBlock(posToCheck);
//	if (type == Maze::BlockType::ice)
//		return true;
//
//	return false;
//}

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
