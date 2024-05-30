#ifndef PLAYERENEMYPREFAB_H
#define PLAYERENEMYPREFAB_H

#include <glm/vec2.hpp>

#include <Prefab.h>

enum class PlayerNumber : char;

class PlayerEnemyPrefab final : public real::Prefab
{
public:
	explicit PlayerEnemyPrefab(real::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber player);
	explicit PlayerEnemyPrefab(real::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber player);
	virtual ~PlayerEnemyPrefab() override = default;

	PlayerEnemyPrefab(const PlayerEnemyPrefab& other) = delete;
	PlayerEnemyPrefab& operator=(const PlayerEnemyPrefab& rhs) = delete;
	PlayerEnemyPrefab(PlayerEnemyPrefab&& other) = delete;
	PlayerEnemyPrefab& operator=(PlayerEnemyPrefab&& rhs) = delete;

private:
	void Init(const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber player) const;

};

#endif // PLAYERENEMYPREFAB_H