#include "PrintMazeCommand.h"

#include <GameObject.h>

#include "Maze.h"

PrintMazeCommand::PrintMazeCommand(int id, int controllerId, real::GameObject* pGameObject)
	: GameObjectCommand(id, controllerId, pGameObject)
{
	m_pMazeComponent = GetGameObject()->GetComponent<Maze>();
}

void PrintMazeCommand::Execute()
{
	m_pMazeComponent->PrintMaze();
}
