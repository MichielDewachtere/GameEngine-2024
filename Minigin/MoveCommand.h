#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "Command.h"

class MoveCommand final : public dae::GameObjectCommand
{
public:
	explicit MoveCommand(int id, int controllerId, dae::GameObject* pGameObject, const glm::ivec2& direction, int speed);
	virtual ~MoveCommand() override = default;

	MoveCommand(const MoveCommand& other) = delete;
	MoveCommand& operator=(const MoveCommand& rhs) = delete;
	MoveCommand(MoveCommand&& other) = delete;
	MoveCommand& operator=(MoveCommand&& rhs) = delete;

	virtual void Execute() override;

private:
	int m_Speed;
	glm::ivec2 m_Direction;
};

#endif // MOVECOMMAND_H