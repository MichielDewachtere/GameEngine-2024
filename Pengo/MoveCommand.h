#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include <Command.h>

#include "Move.h"

class MoveCommand final : public real::GameObjectCommand
{
public:
	explicit MoveCommand(int id, int controllerId, real::GameObject* pGameObject, Direction direction);
	virtual ~MoveCommand() override = default;

	MoveCommand(const MoveCommand& other) = delete;
	MoveCommand& operator=(const MoveCommand& rhs) = delete;
	MoveCommand(MoveCommand&& other) = delete;
	MoveCommand& operator=(MoveCommand&& rhs) = delete;

	virtual void Execute() override;

private:
	Direction m_Direction;
	Move* m_pMoveComponent;
};

#endif // MOVECOMMAND_H