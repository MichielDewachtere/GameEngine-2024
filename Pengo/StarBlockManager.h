#ifndef STARBLOCK_H
#define STARBLOCK_H

#include <array>
#include <Component.h>
#include <Observer.h>
#include <glm/vec2.hpp>

#include "ColliderComponent.h"
#include "ColliderComponent.h"


namespace dae
{
	class SpriteComponent;
}

class Move;
enum class MoveEvents : bool;

class StarBlockManager final
	: public dae::Component
	, public dae::Observer<MoveEvents, const glm::ivec2&>
{
public:
	explicit StarBlockManager(dae::GameObject* pOwner);
	virtual ~StarBlockManager() override;

	StarBlockManager(const StarBlockManager& other) = delete;
	StarBlockManager& operator=(const StarBlockManager& rhs) = delete;
	StarBlockManager(StarBlockManager&& other) = delete;
	StarBlockManager& operator=(StarBlockManager&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	virtual void HandleEvent(MoveEvents, const glm::ivec2&) override;
	virtual void OnSubjectDestroy() override;

	void AddStarBlock(dae::GameObject* go, const glm::ivec2&);

private:
	enum class Orientation : char
	{
		none,
		horizontal,
		vertical
	};

	Orientation m_Orientation{ Orientation::none };
	bool m_BonusAdded{ false }, m_IsTouchingWall{ false };
	int m_AdjacentBlocks{ 0 };
	std::array<std::pair<dae::GameObject*, glm::ivec2>, 3> m_pStarBlocks{};

	void GatherPositions();
	void CheckAdjacentBlocks();
	bool IsAdjacent(const glm::ivec2& pos1, const glm::ivec2& pos2);
	bool IsTouchingWall(const glm::ivec2& pos) const;
	void RemoveObserver();
};

#endif // STARBLOCK_H
