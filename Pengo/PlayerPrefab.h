#ifndef PLAYERPREFAB_H
#define PLAYERPREFAB_H

#include <glm/vec2.hpp>

#include <Prefab.h>

enum class PlayerNumber : char;

class PlayerPrefab final : public real::Prefab
{
public:
	explicit PlayerPrefab(real::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber player);
	explicit PlayerPrefab(real::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber player);
	virtual ~PlayerPrefab() override = default;

	PlayerPrefab(const PlayerPrefab& other) = delete;
	PlayerPrefab& operator=(const PlayerPrefab& rhs) = delete;
	PlayerPrefab(PlayerPrefab&& other) = delete;
	PlayerPrefab& operator=(PlayerPrefab&& rhs) = delete;

	void Init(const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber player) const;

private:

};

#endif // PLAYERPREFAB_H