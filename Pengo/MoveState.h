#ifndef MOVESTATE_H
#define MOVESTATE_H

#include <map>
#include <vector>

#include "IEnemyState.h"
#include "Maze.h"

class Maze;
enum class Direction : char;

namespace real
{
	class SpriteComponent;
}

class Move;

class MoveState : public IEnemyState
{
public:
	explicit MoveState(real::GameObject* pOwner);
	virtual ~MoveState() override = default;

	MoveState(const MoveState& other) = delete;
	MoveState& operator=(const MoveState& rhs) = delete;
	MoveState(MoveState&& other) = delete;
	MoveState& operator=(MoveState&& rhs) = delete;

	virtual void Enter() override;
	virtual IEnemyState* Update() override;
	virtual void Exit() override;

protected:
	virtual void MoveEnemy() const;
	bool GetPoints(Direction direction, std::vector<Direction>& points, bool ignoreIce) const;
	std::pair<Maze::BlockType, bool> IsObstacle(Direction direction, bool ignoreIce) const;
	bool IsIce(Direction direction) const;

	void CheckForPlayer() const;

	Move* GetMoveComponent() const { return m_pMoveComponent; }
	Maze* GetMazeComponent() const { return m_pMazeComponent; }
	real::SpriteComponent* GetSpriteComponent() const { return m_pSpriteComponent; }
	static std::map<int, Move*> GetPlayers() { return m_Players; }

private:
	Move* m_pMoveComponent{ nullptr };
	Maze* m_pMazeComponent{ nullptr };
	real::SpriteComponent* m_pSpriteComponent{ nullptr };
	static inline std::map<int, Move*> m_Players{};

	void RegisterPlayers() const;

	static int GetValue(int max);
};

#endif // MOVESTATE_H