#ifndef DIEDSTATE_H
#define DIEDSTATE_H

#include "IEnemyState.h"

class DiedState final : public IEnemyState
{
public:
	explicit DiedState(real::GameObject* pOwner);
	virtual ~DiedState() override = default;

	DiedState(const DiedState& other) = delete;
	DiedState& operator=(const DiedState& rhs) = delete;
	DiedState(DiedState&& other) = delete;
	DiedState& operator=(DiedState&& rhs) = delete;

	virtual IEnemyState* Update() override;

private:
	
};

#endif // DIEDSTATE_H