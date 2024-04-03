#include "Pushable.h"

#include <GameObject.h>

#include "Enemy.h"
#include "GameUtil.h"
#include "HUD.h"
#include "Move.h"
#include "Maze.h"
#include "ScoreDisplay.h"

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
		if (m_pMazeComponent->GetBlock(m_pMoveComponent->GetMazePos()) != Maze::BlockType::enemy 
			&& m_pMazeComponent->GetBlock(m_pMoveComponent->GetMazePos()) != Maze::BlockType::air)
		{
			const auto mazePos = m_pMoveComponent->GetMazePos();
			const auto posToCheck = mazePos + DirectionToVector(m_Direction);
			auto [type, go] = m_pMazeComponent->GetBlockAndObject(posToCheck);

			if (type == Maze::BlockType::enemy)
			{
				bool encounteredEnemy = false;
				for (const auto & e : m_EnemiesPushed)
				{
					if (e->GetId() == go->GetId())
					{
						encounteredEnemy = true;
						break;
					}
				}

				if (encounteredEnemy == false)
				{
					go->GetComponent<Enemy>()->Push(m_Direction);
					m_EnemiesPushed.push_back(go);
				}
			}
		}

		if (m_pMoveComponent->IsMoving() == false)
			m_Pushed = false;
	}
	else if (m_EnemiesPushed.empty() == false)
	{
		// TODO: Add points
		switch (m_EnemiesPushed.size())
		{
		case 1:
			HUD::GetInstance().AddScore(ScoreEvents::kill);
			std::cout << "+400\n";
			break;
		case 2:
			HUD::GetInstance().AddScore(ScoreEvents::doubleKill);
			std::cout << "+1600\n";
			break;
		case 3:
			HUD::GetInstance().AddScore(ScoreEvents::tripleKill);
			std::cout << "+3200\n";
			break;
		case 4:
			HUD::GetInstance().AddScore(ScoreEvents::quadKill);
			std::cout << "+6400\n";
			break;
		}

		enemiesCrushed.Notify(static_cast<int>(m_EnemiesPushed.size()));

		m_EnemiesPushed.clear();
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
