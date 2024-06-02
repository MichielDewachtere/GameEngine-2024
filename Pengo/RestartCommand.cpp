#include "RestartCommand.h"

#include <SceneManager.h>

#include "Game.h"
#include "GameInfo.h"
#include "HUD.h"
#include "Locator.h"
#include "PlayerManager.h"

RestartCommand::RestartCommand(int id, int controllerId)
	: Command(id, controllerId)
{
}

void RestartCommand::Execute()
{
	Game::Reset();

	HUD::GetInstance().Reset();
	PlayerManager::GetInstance().Reset();

	real::Locator::GetAudioSystem().StopAllSounds();
	real::SceneManager::GetInstance().SetSceneActive(Scenes::start_menu);
}
