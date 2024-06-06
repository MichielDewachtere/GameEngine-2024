#ifndef STARBLOCK_H
#define STARBLOCK_H

#include <array>
#include <Component.h>
#include <Observer.h>
#include <glm/vec2.hpp>

enum class ScoreEvents : char;

namespace real
{
	class SpriteComponent;
}

class Move;
enum class MoveEvents : bool;

class StarBlockManager final
	: public real::Component
	, public real::Observer<MoveEvents, const glm::ivec2&>
{
public:
	explicit StarBlockManager(real::GameObject* pOwner);
	virtual ~StarBlockManager() override;

	StarBlockManager(const StarBlockManager& other) = delete;
	StarBlockManager& operator=(const StarBlockManager& rhs) = delete;
	StarBlockManager(StarBlockManager&& other) = delete;
	StarBlockManager& operator=(StarBlockManager&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;
	virtual void Kill() override;

	virtual void HandleEvent(MoveEvents, const glm::ivec2&) override;
	virtual void OnSubjectDestroy() override {}

	void AddStarBlock(real::GameObject* go, const glm::ivec2&);

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
	std::array<std::pair<real::GameObject*, glm::ivec2>, 3> m_pStarBlocks{};

	void GatherPositions();
	void CheckAdjacentBlocks();
	bool IsAdjacent(const glm::ivec2& pos1, const glm::ivec2& pos2);
	bool IsTouchingWall(const glm::ivec2& pos) const;
	void RemoveObserver();
	static void AddScore(ScoreEvents score);
};

#endif // STARBLOCK_H
