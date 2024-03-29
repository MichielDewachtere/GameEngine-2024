#ifndef SPAWNSTATE_H
#define SPAWNSTATE_H

#include "IEnemyState.h"

namespace dae
{
	class SpriteComponent;
}

class SpawnState final : public IEnemyState
{
public:
	explicit SpawnState(dae::GameObject* pOwner);
	virtual ~SpawnState() override = default;

	SpawnState(const SpawnState& other) = delete;
	SpawnState& operator=(const SpawnState& rhs) = delete;
	SpawnState(SpawnState&& other) = delete;
	SpawnState& operator=(SpawnState&& rhs) = delete;

	virtual void Enter() override;
	virtual IEnemyState* Update() override;
	virtual void Exit() override;

private:
	dae::SpriteComponent* m_pSpriteComponent{ nullptr };
};

#endif // SPAWNSTATE_H