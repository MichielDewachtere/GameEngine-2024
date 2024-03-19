#ifndef CHANGESCORECOMMAND_H
#define CHANGESCORECOMMAND_H

#include "Command.h"
#include "Player.h"

class ChangeScoreCommand final : public dae::GameObjectCommand
{
public:
	explicit ChangeScoreCommand(int id, int controllerId, dae::GameObject* pOwner, int scoreChange);
	virtual ~ChangeScoreCommand() override = default;

	ChangeScoreCommand(const ChangeScoreCommand& other) = delete;
	ChangeScoreCommand& operator=(const ChangeScoreCommand& rhs) = delete;
	ChangeScoreCommand(ChangeScoreCommand&& other) = delete;
	ChangeScoreCommand& operator=(ChangeScoreCommand&& rhs) = delete;

	virtual void Execute() override;

private:
	int m_ScoreChange;
	Player* m_pPlayer{ nullptr };
};

#endif // CHANGESCORECOMMAND_H