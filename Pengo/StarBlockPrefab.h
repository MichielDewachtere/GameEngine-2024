﻿#ifndef STARBLOCKPREFAB_H
#define STARBLOCKPREFAB_H

#include <glm/vec2.hpp>

#include <Prefab.h>

class StarBlockPrefab final : public real::Prefab
{
public:
	explicit StarBlockPrefab(real::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos);
	explicit StarBlockPrefab(real::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos);
	virtual ~StarBlockPrefab() override = default;

	StarBlockPrefab(const StarBlockPrefab& other) = delete;
	StarBlockPrefab& operator=(const StarBlockPrefab& rhs) = delete;
	StarBlockPrefab(StarBlockPrefab&& other) = delete;
	StarBlockPrefab& operator=(StarBlockPrefab&& rhs) = delete;

protected:
	void Init(const glm::ivec2& pos, const glm::ivec2& mazePos) const;
};

#endif // STARBLOCKPREFAB_H