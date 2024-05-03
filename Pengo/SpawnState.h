#ifndef SPAWNSTATE_H
#define SPAWNSTATE_H

#include "IEnemyState.h"

namespace real
{
	class SpriteComponent;
}

class SpawnState final : public IEnemyState
{
public:
	explicit SpawnState(real::GameObject* pOwner, bool deSpawn = false);
	virtual ~SpawnState() override = default;

	SpawnState(const SpawnState& other) = delete;
	SpawnState& operator=(const SpawnState& rhs) = delete;
	SpawnState(SpawnState&& other) = delete;
	SpawnState& operator=(SpawnState&& rhs) = delete;

	virtual void Enter() override;
	virtual IEnemyState* Update() override;
	virtual void Exit() override;

private:
	bool m_DeSpawn;
	real::SpriteComponent* m_pSpriteComponent{ nullptr };
};

#endif // SPAWNSTATE_H