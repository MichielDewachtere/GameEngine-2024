#ifndef ICEPREFAB_H
#define ICEPREFAB_H

#include <glm/vec2.hpp>

#include <Prefab.h>

class IcePrefab final : public dae::Prefab
{
public:
	explicit IcePrefab(dae::GameObject* pOwner, const glm::ivec2& pos);
	explicit IcePrefab(dae::Scene* pScene, const glm::ivec2& pos);
	virtual ~IcePrefab() override = default;

	IcePrefab(const IcePrefab& other) = delete;
	IcePrefab& operator=(const IcePrefab& rhs) = delete;
	IcePrefab(IcePrefab&& other) = delete;
	IcePrefab& operator=(IcePrefab&& rhs) = delete;

protected:
	void Init(const glm::ivec2& pos);
};

#endif // ICEPREFAB_H