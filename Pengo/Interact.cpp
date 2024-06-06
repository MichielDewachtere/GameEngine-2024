// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppIncompleteSwitchStatement
// ReSharper disable CppClangTidyClangDiagnosticSwitch
#include "Interact.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "GameInfo.h"
#include "GameUtil.h"
#include "HUD.h"
#include "IceBlock.h"
#include "Locator.h"
#include "Maze.h"
#include "Move.h"
#include "Player.h"
#include "Pushable.h"
#include "ScoreDisplay.h"
#include "Wall.h"

Interact::Interact(real::GameObject* pOwner)
	: Component(pOwner)
{
}

void Interact::Start()
{
	m_pMaze = GetOwner()->GetParent()->GetComponent<Maze>();
	m_pMove = GetOwner()->GetComponent<Move>();
	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();
	m_pPlayer = GetOwner()->GetComponent<Player>();
}

void Interact::Update()
{
	if (m_IsAnimating)
	{
		if (m_pSpriteComponent->IsAnimationPlaying() == false)
		{
			m_IsAnimating = false;

			m_pMove->Enable();
			m_pMove->Animate(true);
		}
	}
}

void Interact::AttemptInteraction()
{
	const auto direction = m_pMove->GetDirection();
	const auto targetedPos = m_pMove->GetMazePos() + DirectionToVector(direction);
	const auto [blockType, objects] = m_pMaze->GetBlockAndObject(targetedPos);

	if (blockType == Maze::BlockType::ice
		|| blockType == Maze::BlockType::star
		|| blockType == Maze::BlockType::egg)
	{
		const auto icePath = targetedPos + DirectionToVector(direction);

		for (const auto& object : objects)
		{
			if ((m_pMaze->IsOccupied(icePath) || m_pPlayer->IsEnemy()) && blockType != Maze::BlockType::star)
			{
				object->GetComponent<IceBlock>()->Break(m_pPlayer->GetPlayerNumber());
			}
			else if (m_pPlayer->IsEnemy() == false)
			{
				real::Locator::GetAudioSystem().Play(Sounds::push_ice);
				if (const auto pushable = object->GetComponent<Pushable>())
					pushable->Push(direction, m_pPlayer->GetPlayerNumber());
			}
		}

		Animate(direction);
	}
	else if (blockType == Maze::BlockType::wall && m_pPlayer->IsEnemy() == false)
	{
		real::Locator::GetAudioSystem().Play(Sounds::push_wall);

		switch (direction)
		{
		case Direction::up:
			m_pMaze->GetWall(WallOrientation::north)->GetComponent<Wall>()->Shake();
			break;
		case Direction::right:
			m_pMaze->GetWall(WallOrientation::east)->GetComponent<Wall>()->Shake();
			break;
		case Direction::left:
			m_pMaze->GetWall(WallOrientation::west)->GetComponent<Wall>()->Shake();
			break;
		case Direction::down:
			m_pMaze->GetWall(WallOrientation::south)->GetComponent<Wall>()->Shake();
			break;
		}

		Animate(direction);
	}
}

void Interact::BindAnimationToDirection(Direction dir, std::pair<int, int> indices)
{
	m_DirectionToAnimation[dir] = indices;
}

void Interact::Animate(Direction dir)
{
	m_pMove->Animate(false);
	m_pMove->Disable();

	m_IsAnimating = true;

	m_pSpriteComponent->PlayAnimation(m_DirectionToAnimation[dir].first, m_DirectionToAnimation[dir].second, 1);

	//switch (dir)
	//{
	//case Direction::up:
	//	m_pSpriteComponent->PlayAnimation(12, 13, 1);
	//	break;
	//case Direction::right:
	//	m_pSpriteComponent->PlayAnimation(14, 15, 1);
	//	break;
	//case Direction::left:
	//	m_pSpriteComponent->PlayAnimation(10, 11, 1);
	//	break;
	//case Direction::down:
	//	m_pSpriteComponent->PlayAnimation(8, 9, 1);
	//	break;
	//}
}
