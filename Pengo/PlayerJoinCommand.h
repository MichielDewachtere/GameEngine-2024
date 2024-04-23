﻿#ifndef PLAYERJOINCOMMAND_H
#define PLAYERJOINCOMMAND_H

#include <Command.h>
#include <vector>

class PlayerJoinCommand final : public real::GameObjectCommand
{
public:
	explicit PlayerJoinCommand(int id, int controllerId, real::GameObject* pGameObject, std::vector<int> playerIdcs);
	virtual ~PlayerJoinCommand() override = default;

	PlayerJoinCommand(const PlayerJoinCommand& other) = delete;
	PlayerJoinCommand& operator=(const PlayerJoinCommand& rhs) = delete;
	PlayerJoinCommand(PlayerJoinCommand&& other) = delete;
	PlayerJoinCommand& operator=(PlayerJoinCommand&& rhs) = delete;

	virtual void Execute() override;

private:
	std::vector<int> m_PlayerIdcs, m_ControllersRegistered{};
	static inline int m_CurrentPlayer{ 0 };
};

#endif // PLAYERJOINCOMMAND_H