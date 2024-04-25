#ifndef HANDLENAMECOMMAND_H
#define HANDLENAMECOMMAND_H

#include <Command.h>

class EnterName;

class HandleNameCommand final : public real::GameObjectCommand
{
public:
	explicit HandleNameCommand(int id, int controllerId, real::GameObject* pGameObject, bool enter, bool up);
	virtual ~HandleNameCommand() override = default;

	HandleNameCommand(const HandleNameCommand& other) = delete;
	HandleNameCommand& operator=(const HandleNameCommand& rhs) = delete;
	HandleNameCommand(HandleNameCommand&& other) = delete;
	HandleNameCommand& operator=(HandleNameCommand&& rhs) = delete;

	virtual void Start() override;
	virtual void Execute() override;

private:
	bool m_Enter, m_Up;
	EnterName* m_pEnterNameComponent{ nullptr };
};

#endif // HANDLENAMECOMMAND_H