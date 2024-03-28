﻿#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <stdint.h>
#include <vector>

#include <Singleton.h>

#include "Observer.h"

enum class GameEvents : bool;

namespace dae
{
	class GameObject;
}

struct PlayerInfo
{
	dae::GameObject* object;
	bool useKeyboard;
	uint8_t controllerId;
};

class PlayerManager final
	: public dae::Singleton<PlayerManager>
	, public dae::Observer<GameEvents>
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
	void AddPlayer(dae::GameObject* pPlayer);

private:
	friend class Singleton<PlayerManager>;
	explicit PlayerManager() = default;
	uint8_t m_AmountOfPlayers{ 0 };
	std::vector<PlayerInfo> m_pPlayers;
};

#endif // PLAYERMANAGER_H