#ifndef PLAYERPREFAB_H
#define PLAYERPREFAB_H

#include <glm/vec2.hpp>

#include <Prefab.h>

class PlayerPrefab final : public dae::Prefab
{
public:
	explicit PlayerPrefab(dae::GameObject* pOwner, const glm::ivec2& pos);
	explicit PlayerPrefab(dae::Scene* pScene, const glm::ivec2& pos);
	virtual ~PlayerPrefab() override = default;

	PlayerPrefab(const PlayerPrefab& other) = delete;
	PlayerPrefab& operator=(const PlayerPrefab& rhs) = delete;
	PlayerPrefab(PlayerPrefab&& other) = delete;
	PlayerPrefab& operator=(PlayerPrefab&& rhs) = delete;

	void Init(const glm::ivec2& pos);

private:

};

#endif // PLAYERPREFAB_H