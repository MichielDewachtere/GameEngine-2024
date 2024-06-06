#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <stdint.h>
#include <vector>

#include <Singleton.h>
#include <glm/vec2.hpp>

#include "Observer.h"

enum class GameEvents : char;

namespace real
{
	class GameObject;
}

enum class ECharacterColors : uint8_t
{
	blue = 0,
	green = 1,
	red = 2,
	yellow = 3,
	pink = 4,
	orange = 5,
	lightYellow = 6,
	cyan = 7,
	gold = 8,
	amountOfColors = 9
};

struct PlayerInfo
{
	real::GameObject* object;
	glm::ivec2 spawnPos;
	bool useKeyboard;
	uint8_t controllerId;
	bool isEnemy;
	ECharacterColors color;
};

class PlayerManager final
	: public real::Singleton<PlayerManager>
	, public real::Observer<GameEvents>
{
public:
	~PlayerManager() override = default;

	PlayerManager(const PlayerManager& other) = delete;
	PlayerManager& operator=(const PlayerManager& rhs) = delete;
	PlayerManager(PlayerManager&& other) = delete;
	PlayerManager& operator=(PlayerManager&& rhs) = delete;

	void Reset();

	void HandleEvent(GameEvents) override;
	void OnSubjectDestroy() override;

	void SetAmountOfPlayers(int amount, bool isPvp);
	void SetPlayerInput(int player, bool keyboard, uint8_t controllerId = UCHAR_MAX);
	void SetObjectAndPosition(int player, real::GameObject* pPlayer, const glm::ivec2& spawnPos);

	bool RequestPlayer() const;
	uint8_t GetAmountOfPlayers() const { return m_AmountOfPlayers; }
	const std::vector<PlayerInfo>& GetPlayers() { return m_pPlayers; }
	uint8_t GetAmountOfActivePlayers() const;

	PlayerInfo GetPlayerInfo(int player) const;

	ECharacterColors GetRandomColor();

private:
	friend class Singleton<PlayerManager>;
	explicit PlayerManager() = default;
	uint8_t m_AmountOfPlayers{ 0 };
	std::vector<PlayerInfo> m_pPlayers;
};

#endif // PLAYERMANAGER_H