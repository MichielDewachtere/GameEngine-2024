#include "StartGameCommand.h"

#include <SceneManager.h>

StartGameCommand::StartGameCommand(int id, int controllerId)
	: Command(id, controllerId)
{
}

void StartGameCommand::Execute()
{
	if (m_IsFirstFrame)
	{
		m_IsFirstFrame = false;
		return;
	}

	real::SceneManager::GetInstance().SetSceneActive("level1");
}
