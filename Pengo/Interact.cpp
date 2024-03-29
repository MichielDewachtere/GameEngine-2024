// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppIncompleteSwitchStatement
// ReSharper disable CppClangTidyClangDiagnosticSwitch
#include "Interact.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "GameUtil.h"
#include "IceBlock.h"
#include "Maze.h"
#include "Move.h"
#include "Pushable.h"
#include "Wall.h"

Interact::Interact(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

void Interact::Start()
{
	m_pMaze = GetOwner()->GetParent()->GetComponent<Maze>();
	m_pMove = GetOwner()->GetComponent<Move>();
	m_pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();
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
	const auto targetedBlock = m_pMaze->GetBlockAndObject(targetedPos);

	if (targetedBlock.first == Maze::BlockType::ice
		|| targetedBlock.first == Maze::BlockType::star
		|| targetedBlock.first == Maze::BlockType::egg)
	{
		const auto icePath = targetedPos + DirectionToVector(direction);

		if (m_pMaze->IsOccupied(icePath) && targetedBlock.first != Maze::BlockType::star)
		{
			targetedBlock.second->GetComponent<IceBlock>()->Break();
		}
		else
		{
			targetedBlock.second->GetComponent<Pushable>()->Push(direction);
		}

		Animate(direction);
	}
	else if (targetedBlock.first == Maze::BlockType::wall)
	{
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

void Interact::Animate(Direction dir)
{
	m_pMove->Animate(false);
	m_pMove->Disable();

	m_IsAnimating = true;

	switch (dir)
	{
	case Direction::up:
		m_pSpriteComponent->PlayAnimation(12, 13, 1);
		break;
	case Direction::right:
		m_pSpriteComponent->PlayAnimation(14, 15, 1);
		break;
	case Direction::left:
		m_pSpriteComponent->PlayAnimation(10, 11, 1);
		break;
	case Direction::down:
		m_pSpriteComponent->PlayAnimation(8, 9, 1);
		break;
	}
}