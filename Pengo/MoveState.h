#ifndef MOVESTATE_H
#define MOVESTATE_H

#include <vector>

#include "IEnemyState.h"

namespace dae
{
	class SpriteComponent;
}

class Move;

class MoveState final : public IEnemyState
{
public:
	explicit MoveState(dae::GameObject* pOwner);
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
	dae::SpriteComponent* m_pSpriteComponent{ nullptr };
	static inline std::vector<Move*> m_Players{};

	void RegisterPlayers();

};

#endif // MOVESTATE_H