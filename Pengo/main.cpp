#include <exception>
#include <iostream>

#ifdef _DEBUG
//#include <vld.h>
#endif 

#include <RealEngine.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <InputManager.h>

#include "BonusTimeMenu.h"
#include "GameInfo.h"
#include "HUD.h"
#include "Level.h"
#include "LevelGenerator.h"
#include "Macros.h"
#include "PlayerManager.h"

real::WindowSettings g_windowSettings;

void load()
{
	using namespace real;

	LevelGenerator::GetInstance().GenerateLevel();

	auto& input = InputManager::GetInstance();
	input.EnableGamePadInput(true);
	input.AddInputMap(InputMaps::gameplay);
	input.SetInputMapActive(InputMaps::gameplay);


	const auto idcs = input.RegisterGamePads();
	if (idcs.empty())
	{
		PlayerManager::GetInstance().RegisterPlayer({ nullptr, {}, true, UCHAR_MAX });
	}
	else if (idcs.size() == 1)
	{
		PlayerManager::GetInstance().RegisterPlayer({ nullptr, {}, true, UCHAR_MAX });
		PlayerManager::GetInstance().RegisterPlayer({ nullptr, {}, false, idcs.front() });
	}
	else
	{
		constexpr int maxAmountOfPlayers = 2;
		for (int i = 0; i < maxAmountOfPlayers; ++i)
		{
			PlayerManager::GetInstance().RegisterPlayer({ nullptr, {}, false, idcs[i] });
		}
	}

	// Create the HUD
	HUD::GetInstance().Init();

	// TODO: Add Menu's
	SceneManager::GetInstance().CreateScene(new BonusTimeMenu(Scenes::bonus_menu, "none", g_windowSettings));

	SceneManager::GetInstance().CreateScene(new Level("level1", InputMaps::gameplay, true));
	SceneManager::GetInstance().CreateScene(new Level("level2", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level3", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level4", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level5", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level6", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level7", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level8", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level9", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level10", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level11", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level12", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level13", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level14", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level15", InputMaps::gameplay));
	SceneManager::GetInstance().CreateScene(new Level("level16", InputMaps::gameplay));

	SceneManager::GetInstance().SetSceneActive("level1");
}

int main(int, char* [])
{
	g_windowSettings.windowTitle = "Prog 4 Engine";
	g_windowSettings.dataPath = "../Data/";
	g_windowSettings.fps = 60;
	g_windowSettings.width = BLOCK_SIZE * (MAZE_WIDTH + 1 /*2 walls*/) * PIXEL_SCALE;
	g_windowSettings.height = BLOCK_SIZE * PIXEL_SCALE * (MAZE_HEIGHT + 1 /* 2 walls */) + HUD_SIZE_BOTTOM + HUD_SIZE_TOP;

	real::RealEngine engine(g_windowSettings);
	engine.Run(load);

	//try
	//{
	//	real::RealEngine engine(g_windowSettings);
	//	engine.Run(load);
	//}
	//catch (std::exception& e)
	//{
	//	std::cout << e.what();
	//}

	return 0;
}