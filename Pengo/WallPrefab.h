#ifndef WALLPREFAB_H
#define WALLPREFAB_H

#include <glm/vec2.hpp>

#include <Prefab.h>

enum class WallOrientation : char;

class WallPrefab final : public real::Prefab
{
public:
	explicit WallPrefab(real::GameObject* pOwner, const glm::ivec2& pos, bool horizontal, WallOrientation orientation);
	explicit WallPrefab(real::Scene* pScene, const glm::ivec2& pos, bool horizontal, WallOrientation orientation);
	virtual ~WallPrefab() override = default;

	WallPrefab(const WallPrefab& other) = delete;
	WallPrefab& operator=(const WallPrefab& rhs) = delete;
	WallPrefab(WallPrefab&& other) = delete;
	WallPrefab& operator=(WallPrefab&& rhs) = delete;

protected:
	void Init(const glm::ivec2& pos, bool horizontal, WallOrientation orientation);
};


#endif // WALLPREFAB_H