#ifndef ICEBREAKSTATE_H
#define ICEBREAKSTATE_H

#include "MoveState.h"

class IceBreakState : public MoveState
{
public:
	explicit IceBreakState(real::GameObject* pOwner);
	virtual ~IceBreakState() override = default;

	IceBreakState(const IceBreakState& other) = delete;
	IceBreakState& operator=(const IceBreakState& rhs) = delete;
	IceBreakState(IceBreakState&& other) = delete;
	IceBreakState& operator=(IceBreakState&& rhs) = delete;

	virtual void Enter() override;
	virtual IEnemyState* Update() override;
	virtual void Exit() override;

private:
	virtual void MoveEnemy() const override;

};

#endif // ICEBREAKSTATE_H