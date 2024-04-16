#ifndef PRINTMAZECOMMAND_H
#define PRINTMAZECOMMAND_H

#include <Command.h>

class Maze;

class PrintMazeCommand final : public real::GameObjectCommand
{
public:
	explicit PrintMazeCommand(int id, int controllerId, real::GameObject* pGameObject);
	virtual ~PrintMazeCommand() override = default;

	PrintMazeCommand(const PrintMazeCommand& other) = delete;
	PrintMazeCommand& operator=(const PrintMazeCommand& rhs) = delete;
	PrintMazeCommand(PrintMazeCommand&& other) = delete;
	PrintMazeCommand& operator=(PrintMazeCommand&& rhs) = delete;

	virtual void Execute() override;

private:
	Maze* m_pMazeComponent;
};

#endif // PRINTMAZECOMMAND_H