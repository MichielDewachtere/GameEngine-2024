#ifndef INTERACTCOMMAND_H
#define INTERACTCOMMAND_H

#include <Command.h>

class Interact;

class InteractCommand final : public real::GameObjectCommand
{
public:
	explicit InteractCommand(int id, int controllerId, real::GameObject* pGameObject);
	virtual ~InteractCommand() override = default;

	InteractCommand(const InteractCommand& other) = delete;
	InteractCommand& operator=(const InteractCommand& rhs) = delete;
	InteractCommand(InteractCommand&& other) = delete;
	InteractCommand& operator=(InteractCommand&& rhs) = delete;

	virtual void Execute() override;

private:
	Interact* m_pInteractComponent;
};

#endif // INTERACTCOMMAND_H