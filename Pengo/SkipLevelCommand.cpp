#include "SkipLevelCommand.h"

#include "Game.h"
#include "GameInfo.h"
#include "SceneManager.h"

SkipLevelCommand::SkipLevelCommand(int id, int controllerId)
	: Command(id, controllerId)
{
}

void SkipLevelCommand::Execute()
{
	auto level= Game::GetCurrentLevel();
	m_LastLevel = level;
	++level;

	std::string levelName;
	if (m_LastLevel == 16)
		levelName = Scenes::high_score_menu;
	else
		levelName = "level" + std::to_string(level);

	real::SceneManager::GetInstance().SetSceneActive(levelName);
}
