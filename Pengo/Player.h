#ifndef PLAYER_H
#define PLAYER_H

#include <Component.h>

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

class Player final : public real::Component
{
public:
	explicit Player(real::GameObject* pOwner, PlayerNumber number, bool isEnemy);
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

private:
	PlayerNumber m_PlayerNumber;
	bool m_IsDying{ false }, m_IsEnemy{ false };
	real::SpriteComponent* m_pSpriteComponent{ nullptr };
};

#endif // PLAYER_H