#ifndef STARBLOCKPREFAB_H
#define STARBLOCKPREFAB_H

#include <glm/vec2.hpp>

#include <Prefab.h>

class StarBlockPrefab final : public dae::Prefab
{
public:
	explicit StarBlockPrefab(dae::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos);
	explicit StarBlockPrefab(dae::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos);
	virtual ~StarBlockPrefab() override = default;

	StarBlockPrefab(const StarBlockPrefab& other) = delete;
	StarBlockPrefab& operator=(const StarBlockPrefab& rhs) = delete;
	StarBlockPrefab(StarBlockPrefab&& other) = delete;
	StarBlockPrefab& operator=(StarBlockPrefab&& rhs) = delete;

protected:
	void Init(const glm::ivec2& pos, const glm::ivec2& mazePos);
};

#endif // STARBLOCKPREFAB_H