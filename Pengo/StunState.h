#ifndef STUNSTATE_H
#define STUNSTATE_H

#include <vector>
#include <glm/vec2.hpp>

#include "IEnemyState.h"

class Move;

class StunState final : public IEnemyState
{
public:
	explicit StunState(dae::GameObject* pOwner);
	virtual ~StunState() override = default;

	StunState(const StunState& other) = delete;
	StunState& operator=(const StunState& rhs) = delete;
	StunState(StunState&& other) = delete;
	StunState& operator=(StunState&& rhs) = delete;

	virtual void Enter() override;
	virtual IEnemyState* Update() override;
	virtual void Exit() override;

private:
	float m_StunTime{ 5.f }, m_AccuTime{ 0.f };

	glm::ivec2 m_MazePos{};
	std::vector<Move*> m_Players{};

	void RegisterPlayers();
};

#endif // STUNSTATE_H