#ifndef MOVESTATE_H
#define MOVESTATE_H

#include <map>

#include "IEnemyState.h"

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
	real::SpriteComponent* m_pSpriteComponent{ nullptr };
	static inline std::map<int, Move*> m_Players{};

	void RegisterPlayers() const;

};

#endif // MOVESTATE_H