#include "stdafx.h"
#include "LoadSceneCommand.h"

#include "SceneManager.h"

LoadSceneCommand::LoadSceneCommand(int id, int controllerId, std::string sceneName)
	: Command(id, controllerId)
	, m_Name(std::move(sceneName))
{
}

void LoadSceneCommand::Execute()
{
	dae::SceneManager::GetInstance().SetSceneActive(m_Name);
}
