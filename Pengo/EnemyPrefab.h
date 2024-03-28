#ifndef ENEMYPREFAB_H
#define ENEMYPREFAB_H

#include <glm/vec2.hpp>
#include <Prefab.h>

class EnemyPrefab final : public dae::Prefab
{
public:
	explicit EnemyPrefab(dae::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos);
	explicit EnemyPrefab(dae::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos);
	virtual ~EnemyPrefab() override = default;

	EnemyPrefab(const EnemyPrefab& other) = delete;
	EnemyPrefab& operator=(const EnemyPrefab& rhs) = delete;
	EnemyPrefab(EnemyPrefab&& other) = delete;
	EnemyPrefab& operator=(EnemyPrefab&& rhs) = delete;

private:
	void Init(const glm::ivec2& pos, const glm::ivec2& mazePos);
};

#endif // ENEMYPREFAB_H