#ifndef FLEESTATE_H
#define FLEESTATE_H

#include <array>

#include "IceBreakState.h"


class FleeState final : public IceBreakState
{
public:
	explicit FleeState(real::GameObject* pOwner);
	virtual ~FleeState() override = default;

	FleeState(const FleeState& other) = delete;
	FleeState& operator=(const FleeState& rhs) = delete;
	FleeState(FleeState&& other) = delete;
	FleeState& operator=(FleeState&& rhs) = delete;

	virtual void Enter() override;
	virtual IEnemyState* Update() override;
	virtual void Exit() override;

private:

	glm::ivec2 m_ClosestCorner{ 0,0 };

	virtual void MoveEnemy() const override;
	bool IsValidCorner(const glm::ivec2& corner) const;

	static constexpr inline std::array<glm::ivec2, 4> possible_corners = {
		glm::ivec2{0,0},
		glm::ivec2{0,14},
		glm::ivec2{12,0},
		glm::ivec2{12,14},
	};
};

#endif // FLEESTATE_H