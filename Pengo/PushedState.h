#ifndef PUSHEDSTATE_H
#define PUSHEDSTATE_H

#include <map>
#include <utility>

#include "IEnemyState.h"

enum class Direction : char;

namespace real
{
	class SpriteComponent;
}

class Pushable;

class PushedState final : public IEnemyState
{
public:
	explicit PushedState(real::GameObject* pOwner);
	virtual ~PushedState() override = default;

	PushedState(const PushedState& other) = delete;
	PushedState& operator=(const PushedState& rhs) = delete;
	PushedState(PushedState&& other) = delete;
	PushedState& operator=(PushedState&& rhs) = delete;

	virtual void Enter() override;
	virtual IEnemyState* Update() override;
	virtual void Exit() override;

	void SetDirection(Direction direction) { m_PushDirection = direction; }

private:
	Direction m_PushDirection{};
	Pushable* m_pPushableComponent{ nullptr };
	real::SpriteComponent* m_pSpriteComponent{ nullptr };

	static std::map<Direction, std::pair<int, int>> m_DirectionToSquashAnim;
};

#endif // PUSHEDSTATE_H