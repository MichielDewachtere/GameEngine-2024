#ifndef PLAYER_H
#define PLAYER_H

#include <Component.h>

namespace dae
{
	class SpriteComponent;
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

	virtual void Start() override;
	virtual void Update() override;

	void Die();
	void ReSpawn() const;

private:
	bool m_IsDirty{ false };
	dae::SpriteComponent* m_pSpriteComponent{ nullptr };
};

#endif // PLAYER_H