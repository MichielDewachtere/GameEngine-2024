#ifndef DAMAGECOMMAND_H
#define DAMAGECOMMAND_H

#include "Command.h"
#include "Player.h"

class DamageCommand final : public dae::GameObjectCommand
{
public:
	explicit DamageCommand(int id, int controllerId, dae::GameObject* pOwner);
	virtual ~DamageCommand() override = default;

	DamageCommand(const DamageCommand& other) = delete;
	DamageCommand& operator=(const DamageCommand& rhs) = delete;
	DamageCommand(DamageCommand&& other) = delete;
	DamageCommand& operator=(DamageCommand&& rhs) = delete;

	virtual void Execute() override;

private:
	Player* m_pPlayer{ nullptr };
};

#endif // DAMAGECOMMAND_H