#include "Move.h"

#include <glm/glm.hpp>

#include <GameObject.h>
#include <GameTime.h>
#include <SpriteComponent.h>

#include "GameUtil.h"
#include "Macros.h"
#include "Maze.h"

Move::Move(dae::GameObject* pOwner, const glm::ivec2& pos, Maze::BlockType type, float movementSpeed, bool animate)
	: Component(pOwner)
	, m_MazePosition(pos)
	, m_Type(type)
	, m_MovementSpeed(movementSpeed)
	, m_Animate(animate)
{
	m_pMaze = GetOwner()->GetParent()->GetComponent<Maze>();
	m_pMaze->SetBlock(m_MazePosition, m_Type, GetOwner());
}

void Move::Start()
{
	if (m_Animate)
		m_pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();
}

void Move::Update()
{
	if (m_Move == false)
	{
		if (m_pSpriteComponent && m_Animate)
			m_pSpriteComponent->Pause(true);

		return;
	}

	if (m_Animate && m_pSpriteComponent->IsAnimationPlaying() == false)
	{
		m_pSpriteComponent->PlayAnimation(m_DirectionToAnimation[m_Direction].first, m_DirectionToAnimation[m_Direction].second);
	}

	const auto dt = dae::GameTime::GetInstance().GetElapsed();
	const glm::vec2 t{
		static_cast<float>(m_DirectionVec.x) * m_MovementSpeed * dt,
		static_cast<float>(m_DirectionVec.y) * m_MovementSpeed * dt
	};

	const auto transform = GetOwner()->GetTransform();
	transform->Translate(t);

	if (HasReachedPosition())
	{
		m_Move = false;

		const auto pos = Maze::LocalToMaze(m_NewPosition);
		m_pMaze->SetBlock(m_MazePosition, Maze::BlockType::air, nullptr);
		m_MazePosition = pos;
		m_pMaze->SetBlock(m_MazePosition, m_Type, GetOwner());

		transform->SetLocalPosition(m_NewPosition);

		moved.Notify(MoveEvents::moved, m_MazePosition);

		if (m_MoveUntilStopped)
		{
			MoveInDirection(m_Direction, true);
		}
	}
}

bool Move::MoveInDirection(Direction dir, bool untilStopped)
{
	// TODO: maybe already record second move?
	if (m_Move || IsActive() == false)
		return false;

	m_DirectionVec = DirectionToVector(dir);
	const auto newPos = m_MazePosition + m_DirectionVec;

	if (m_Direction != dir)
	{
		m_Direction = dir;
	}

	if (m_pSpriteComponent && m_Animate)
	{
		m_pSpriteComponent->PlayAnimation(m_DirectionToAnimation[m_Direction].first, m_DirectionToAnimation[m_Direction].second);

		if (m_pSpriteComponent->IsPaused())
			m_pSpriteComponent->Pause(false);
	}

	if (m_pMaze->IsOccupied(newPos))
		return false;

	const glm::vec2 scaledNewPos = Maze::MazeToLocal(newPos);

	m_NewPosition = scaledNewPos;
	m_Move = true;
	m_MoveUntilStopped = untilStopped;
	startedMoving.Notify(MoveEvents::startedMoving);

	return true;
}

void Move::BindAnimationToDirection(Direction dir, const std::pair<int, int> indices)
{
	m_DirectionToAnimation[dir] = indices;
}

bool Move::HasReachedPosition() const
{
	const auto curPos = GetOwner()->GetTransform()->GetLocalPosition();

	return std::abs(m_NewPosition.x - static_cast<int>(curPos.x)) < PIXEL_SCALE * 2
		&& std::abs(static_cast<int>(curPos.y) - m_NewPosition.y) < PIXEL_SCALE * 2;
}
