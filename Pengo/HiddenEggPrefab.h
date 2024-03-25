#ifndef HIDDENEGGPREFAB_H
#define HIDDENEGGPREFAB_H

#include <glm/vec2.hpp>

#include <Prefab.h>

class HiddenEggPrefab final : public dae::Prefab
{
public:
	explicit HiddenEggPrefab(dae::GameObject* pOwner, const glm::ivec2& pos);
	explicit HiddenEggPrefab(dae::Scene* pScene, const glm::ivec2& pos);
	virtual ~HiddenEggPrefab() override = default;

	HiddenEggPrefab(const HiddenEggPrefab& other) = delete;
	HiddenEggPrefab& operator=(const HiddenEggPrefab& rhs) = delete;
	HiddenEggPrefab(HiddenEggPrefab&& other) = delete;
	HiddenEggPrefab& operator=(HiddenEggPrefab&& rhs) = delete;

protected:
	void Init(const glm::ivec2& pos);
};

#endif // HIDDENEGGPREFAB_H