#include "Pushable.h"

#include <GameObject.h>

#include "Enemy.h"
#include "GameUtil.h"
#include "Move.h"
#include "Maze.h"

Pushable::Pushable(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

void Pushable::Start()
{
	m_pMoveComponent = GetOwner()->GetComponent<Move>();
	m_pMazeComponent = GetOwner()->GetParent()->GetComponent<Maze>();
}

void Pushable::Update()
{
	if (m_Pushed)
	{
		if (m_pMazeComponent->GetBlock(m_pMoveComponent->GetMazePos()) != Maze::BlockType::enemy)
		{
			const auto mazePos = m_pMoveComponent->GetMazePos();
			const auto posToCheck = mazePos + DirectionToVector(m_Direction);
			auto [type, go] = m_pMazeComponent->GetBlockAndObject(posToCheck);

			if (type == Maze::BlockType::enemy)
			{
				go->GetComponent<Enemy>()->Push(m_Direction);
			}
		}

		if (m_pMoveComponent->IsMoving() == false)
			m_Pushed = false;
	}
}

void Pushable::Push(Direction direction)
{
	m_pMoveComponent->MoveInDirection(direction, true);
	m_Pushed = true;
	m_Direction = direction;
}

bool Pushable::IsBeingPushed() const
{
	return m_Pushed;
}
