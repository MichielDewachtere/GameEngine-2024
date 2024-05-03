#include "FleeState.h"

#include <random>

#include <GameObject.h>
#include <Utils.h>

#include "GameUtil.h"
#include "IceBlock.h"
#include "Move.h" 
#include "SpawnState.h"

FleeState::FleeState(real::GameObject* pOwner)
	: IceBreakState(pOwner)
{
}

void FleeState::Enter()
{
	IceBreakState::Enter();

	GetMoveComponent()->BindAnimationToDirection(Direction::down, { 24,25 });
	GetMoveComponent()->BindAnimationToDirection(Direction::left, { 26,27 });
	GetMoveComponent()->BindAnimationToDirection(Direction::up, { 28,29 });
	GetMoveComponent()->BindAnimationToDirection(Direction::right, { 30,31 });

	const auto pos = GetMoveComponent()->GetMazePos();
	if (pos.x > 6)
		m_ClosestCorner.x = 12;

	if (pos.y > 7)
		m_ClosestCorner.y = 14;

	int counter = 0;
	while (IsValidCorner(m_ClosestCorner) == false)
	{
		m_ClosestCorner = possible_corners[counter];
		++counter;
	}
}

IEnemyState* FleeState::Update()
{
	if (GetMoveComponent()->IsMoving() == false)
	{
		const auto mazePos = GetMoveComponent()->GetMazePos();
		if (m_ClosestCorner == mazePos)
			return new SpawnState(GetOwner(), true);

		MoveEnemy();
	}

	return nullptr;
}

void FleeState::Exit()
{
	IceBreakState::Exit();
}

void FleeState::MoveEnemy() const
{
	const auto mazePos = GetMoveComponent()->GetMazePos();

	std::vector<Direction> directions;
	std::map<Direction, bool> isIce;
	if (m_ClosestCorner.x < mazePos.x)
		isIce[Direction::left] = GetPoints(Direction::left, directions, false);
	else
		isIce[Direction::right] = GetPoints(Direction::right, directions, false);
	if (m_ClosestCorner.y < mazePos.y)
		isIce[Direction::up] = GetPoints(Direction::up, directions, false);
	else
		isIce[Direction::down] = GetPoints(Direction::down, directions, false);

	std::random_device rd;
	std::mt19937 g(rd());
	std::ranges::shuffle(directions, g);

	if (directions.empty())
	{
		GetMoveComponent()->MoveInDirection(/*InvertDirection(*/GetMoveComponent()->GetDirection()/*)*/);
	}
	else
	{
		const auto dirToGo = directions.front();

		if (isIce[dirToGo])
		{
			const auto icePos = GetMoveComponent()->GetMazePos() + DirectionToVector(dirToGo);
			const auto iceBlock = GetMazeComponent()->GetBlockAndObject(icePos).second.front();

			iceBlock->GetComponent<IceBlock>()->Break();
		}

		GetMoveComponent()->MoveInDirection(dirToGo);
	}
}

bool FleeState::IsValidCorner(const glm::ivec2& corner) const
{
	if (GetMazeComponent()->GetBlock(corner) == Maze::BlockType::star)
		return false;

	return true;
}
