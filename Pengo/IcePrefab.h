#ifndef ICEPREFAB_H
#define ICEPREFAB_H

#include <glm/vec2.hpp>

#include <Prefab.h>

class IcePrefab final : public real::Prefab
{
public:
	explicit IcePrefab(real::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos, bool hidesEgg = false);
	explicit IcePrefab(real::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos, bool hidesEgg = false);
	virtual ~IcePrefab() override = default;

	IcePrefab(const IcePrefab& other) = delete;
	IcePrefab& operator=(const IcePrefab& rhs) = delete;
	IcePrefab(IcePrefab&& other) = delete;
	IcePrefab& operator=(IcePrefab&& rhs) = delete;

protected:
	void Init(const glm::ivec2& pos, const glm::ivec2& mazePos, bool hidesEgg = false);
};

#endif // ICEPREFAB_H