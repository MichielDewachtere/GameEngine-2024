#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <stdint.h>
#include <vector>

#include <Singleton.h>
#include <glm/vec2.hpp>

#include "BonusTimeMenu.h"
#include "Observer.h"

enum class GameEvents : char;

namespace real
{
	class GameObject;
}

struct PlayerInfo
{
	real::GameObject* object;
	glm::ivec2 spawnPos;
	bool useKeyboard;
	uint8_t controllerId;
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

	// TODO: link to subject
	void HandleEvent(GameEvents) override;
	void OnSubjectDestroy() override;

	void RegisterPlayer(PlayerInfo info);

	bool RequestPlayer() const;
	void AddPlayer(real::GameObject* pPlayer, const glm::ivec2&);
	uint8_t GetAmountOfPlayers() const { return m_AmountOfPlayers; }

private:
	friend class Singleton<PlayerManager>;
	explicit PlayerManager() = default;
	uint8_t m_AmountOfPlayers{ 0 };
	std::vector<PlayerInfo> m_pPlayers;
};

#endif // PLAYERMANAGER_H