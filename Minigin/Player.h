#ifndef PLAYER_H
#define PLAYER_H

#include "Component.h"
#include "Subject.h"

namespace dae
{
	class ColliderComponent;
}

class Player final : public dae::Component
{
public:
	explicit Player(dae::GameObject* pOwner);
	virtual ~Player() override = default;

	Player(const Player& other) = delete;
	Player& operator=(const Player& rhs) = delete;
	Player(Player&& other) = delete;
	Player& operator=(Player&& rhs) = delete;

	void Start() override;
	void Update() override;

	void AddScore(int score);
	void Damage();

	void SetEnemy(dae::ColliderComponent* pEnemy) { m_pEnemy = pEnemy; }

	dae::Subject<uint8_t> healthChanged;
	dae::Subject<uint32_t> scoreChanged;

private:
	uint8_t m_Health{ 3 };
	uint32_t m_Score{ 0 };
	bool m_MovePlayer{ false };
	// Test code, will be deleted and changed
	dae::ColliderComponent * m_Self{ nullptr }, * m_pEnemy{ nullptr };
};

#endif // PLAYER_H