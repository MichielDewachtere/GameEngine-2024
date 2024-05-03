#include "IceBreakState.h"

#include <GameObject.h>
#include <random>

#include "EnemyHandler.h"
#include "Move.h"
#include "Game.h"
#include "GameUtil.h"
#include "IceBlock.h"
#include "FleeState.h"

IceBreakState::IceBreakState(real::GameObject* pOwner)
	: MoveState(pOwner)
{
}

void IceBreakState::Enter()
{
	MoveState::Enter();

	GetMoveComponent()->BindAnimationToDirection(Direction::down, { 16,17 });
	GetMoveComponent()->BindAnimationToDirection(Direction::left, { 18,19 });
	GetMoveComponent()->BindAnimationToDirection(Direction::up, { 20,21 });
	GetMoveComponent()->BindAnimationToDirection(Direction::right, { 22,23 });
}

IEnemyState* IceBreakState::Update()
{
	CheckForPlayer();

	if (GetMoveComponent()->IsMoving() == false)
	{
		MoveEnemy();
	}

	if (Game::GetGameTime() > 60 && EnemyHandler::GetAmountOfEnemies() == 1)
		return new FleeState(GetOwner());

	return nullptr;
}

void IceBreakState::Exit()
{
	MoveState::Exit();
}

void IceBreakState::MoveEnemy() const
{
	std::vector<Direction> directions;
	std::map<Direction, bool> isIce;
	isIce[Direction::left] = GetPoints(Direction::left, directions, false);
	isIce[Direction::right] = GetPoints(Direction::right, directions, false);
	isIce[Direction::up] = GetPoints(Direction::up, directions, false);
	isIce[Direction::down] = GetPoints(Direction::down, directions, false);

	std::random_device rd;
	std::mt19937 g(rd());
	std::ranges::shuffle(directions, g);

	if (directions.empty())
	{
		GetMoveComponent()->MoveInDirection(GetMoveComponent()->GetDirection());
	}
	else
	{
		while (directions.empty() == false)
		{

			const auto dirToGo = directions.back();

			if (isIce[dirToGo])
			{
				const auto icePos = GetMoveComponent()->GetMazePos() + DirectionToVector(dirToGo);
				const auto iceBlock = GetMazeComponent()->GetBlockAndObject(icePos).second.front();

				const auto iceComp = iceBlock->GetComponent<IceBlock>();
				if (iceComp->HidesEgg())
				{
					directions.pop_back();
					continue;
				}

				iceComp->Break();
			}

			GetMoveComponent()->MoveInDirection(dirToGo);
			break;
		}
	}
}
