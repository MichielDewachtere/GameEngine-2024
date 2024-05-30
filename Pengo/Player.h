#ifndef PLAYER_H
#define PLAYER_H

#include <Component.h>
#include <cstdint>

namespace real
{
	class SpriteComponent;
}

enum class PlayerNumber : char
{
	playerOne = 0,
	playerTwo = 1,
	none = 2,
};

class Player : public real::Component
{
public:
	explicit Player(real::GameObject* pOwner, PlayerNumber number, bool isEnemy = false);
	virtual ~Player() override = default;

	Player(const Player& other) = delete;
	Player& operator=(const Player& rhs) = delete;
	Player(Player&& other) = delete;
	Player& operator=(Player&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void Die();
	void ReSpawn() const;
	PlayerNumber GetPlayerNumber() const { return m_PlayerNumber; }
	bool IsEnemy() const;

protected:
	uint8_t m_ReSpawnSprite{ 0 };

private:
	PlayerNumber m_PlayerNumber;
	bool m_IsDying{ false }, m_IsEnemy{ false };
	real::SpriteComponent* m_pSpriteComponent{ nullptr };
};

#endif // PLAYER_H