#ifndef LABMOVECOMMAND_H
#define LABMOVECOMMAND_H

#include <glm/vec2.hpp>

#include <Command.h>

class LabMoveCommand final : public dae::GameObjectCommand
{
public:
	explicit LabMoveCommand(int id, int controllerId, dae::GameObject* pGameObject, const glm::ivec2& direction, int speed);
	virtual ~LabMoveCommand() override = default;

	LabMoveCommand(const LabMoveCommand& other) = delete;
	LabMoveCommand& operator=(const LabMoveCommand& rhs) = delete;
	LabMoveCommand(LabMoveCommand&& other) = delete;
	LabMoveCommand& operator=(LabMoveCommand&& rhs) = delete;

	virtual void Execute() override;

private:
	int m_Speed;
	glm::ivec2 m_Direction;
};

#endif // LABMOVECOMMAND_H