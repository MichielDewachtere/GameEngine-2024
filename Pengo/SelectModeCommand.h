#ifndef SELECTMODECOMMAND_H
#define SELECTMODECOMMAND_H

#include <Command.h>

class SelectModeCommand final : public real::GameObjectCommand
{
public:
	explicit SelectModeCommand(int id, int controllerId, real::GameObject* pGameObject, bool confirm, bool goUp);
	virtual ~SelectModeCommand() override = default;

	SelectModeCommand(const SelectModeCommand& other) = delete;
	SelectModeCommand& operator=(const SelectModeCommand& rhs) = delete;
	SelectModeCommand(SelectModeCommand&& other) = delete;
	SelectModeCommand& operator=(SelectModeCommand&& rhs) = delete;

	virtual void Execute() override;

private:
	bool m_Confirm, m_GoUp;
};

#endif // SELECTMODECOMMAND_H