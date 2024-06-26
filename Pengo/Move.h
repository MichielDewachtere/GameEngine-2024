﻿#ifndef MOVE_H
#define MOVE_H

#include <Component.h>
#include <map>
#include <vector>
#include <glm/vec2.hpp>
#include <Subject.h>

#include "Maze.h"

namespace real
{
	class SpriteComponent;
}

enum class Direction : char
{
	up = 0,
	right = 1,
	left = 2,
	down = 3,
	amountOfDirs = 4
};

enum class MoveEvents : bool
{
	startedMoving = 0,
	moved = 1
};

class Move final : public real::Component
{
public:
	explicit Move(real::GameObject* pOwner, const glm::ivec2& pos, Maze::BlockType type, float movementSpeed, bool animate);
	virtual ~Move() override = default;

	Move(const Move& other) = delete;
	Move& operator=(const Move& rhs) = delete;
	Move(Move&& other) = delete;
	Move& operator=(Move&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void Reset();

	bool MoveInDirection(Direction dir, bool untilStopped = false);
	void BindAnimationToDirection(Direction dir, std::pair<int, int> indices);

	void SetMovementSpeed(float speed) { m_MovementSpeed = speed; }
	void SetMazePos(const glm::ivec2& newPos);

	Direction GetDirection() const { return m_Direction; }
	const glm::ivec2& GetMazePos() const { return m_MazePosition; }
	Maze::BlockType GetType() const { return m_Type; }

	void StopMoving();
	bool IsMoving() const { return m_Move; }
	void Animate(bool animate) { m_Animate = animate; }

	real::Subject<MoveEvents> startedMoving;
	real::Subject<MoveEvents, const glm::ivec2&> moved;

private:
	glm::ivec2 m_MazePosition, m_NewPosition{}, m_DirectionVec{};
	Direction m_Direction{ Direction::amountOfDirs };
	Maze::BlockType m_Type;
	float m_MovementSpeed;
	bool m_Move{ false }, m_MoveUntilStopped{ false }, m_Animate;

	Maze* m_pMaze{ nullptr };
	real::SpriteComponent* m_pSpriteComponent{ nullptr };
	std::map<Direction, std::pair<int, int>> m_DirectionToAnimation;

	bool HasReachedPosition() const;
};

#endif // MOVE_H