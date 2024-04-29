#ifndef MOVESTATE_H
#define MOVESTATE_H

#include <map>

#include "IEnemyState.h"

class Maze;
enum class Direction : char;

namespace real
{
	class SpriteComponent;
}

class Move;

class MoveState final : public IEnemyState
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
private:
	Move* m_pMoveComponent{ nullptr };
	Maze* m_pMazeComponent{ nullptr };
	real::SpriteComponent* m_pSpriteComponent{ nullptr };
	static inline std::map<int, Move*> m_Players{};

	void RegisterPlayers() const;

	void MoveEnemy();
	int GetPoints(Direction direction);
	bool IsObstacle(Direction direction);
	bool IsIce(Direction direction);

	static int GetValue(int max);
};

#endif // MOVESTATE_H