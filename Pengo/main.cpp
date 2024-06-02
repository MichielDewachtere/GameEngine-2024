#include <exception>
#include <iostream>

#ifdef _DEBUG
//#include <vld.h>
#endif 

#include <chrono>
#include <RealEngine.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <InputManager.h>

#include "BonusTimeMenu.h"
#include "GameInfo.h"
#include "GameOverMenu.h"
#include "HUD.h"
#include "Level.h"
#include "LevelGenerator.h"
#include "Macros.h"
#include "StartMenu.h"
#include "HighScoreMenu.h"

real::WindowSettings g_windowSettings;

void load()
{
	using namespace real;

	std::srand(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));

	LevelGenerator::GetInstance().GenerateLevel();

	auto& input = InputManager::GetInstance();
	input.EnableGamePadInput(true);
	input.RegisterGamePads();
	input.AddInputMap(InputMaps::start_menu);
	input.AddInputMap(InputMaps::bonus_time_menu);
	input.AddInputMap(InputMaps::gameplay);
	input.AddInputMap(InputMaps::game_over_menu);
	input.AddInputMap(InputMaps::high_score_menu);
	input.SetInputMapActive(InputMaps::start_menu);

	// Create the HUD
	HUD::GetInstance().Init();

	SceneManager::GetInstance().CreateScene(new StartMenu(Scenes::start_menu, "none", g_windowSettings));
	SceneManager::GetInstance().CreateScene(new BonusTimeMenu(Scenes::bonus_menu, "none", g_windowSettings));
	SceneManager::GetInstance().CreateScene(new HighScoreMenu(Scenes::high_score_menu, InputMaps::high_score_menu, g_windowSettings));
	SceneManager::GetInstance().CreateScene(new GameOverMenu(Scenes::game_over_menu, "none", g_windowSettings));

	SceneManager::GetInstance().CreateScene(new Level("level1", InputMaps::gameplay, false));
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

	SceneManager::GetInstance().SetSceneActive(Scenes::start_menu);
}

int main(int, char* [])
{
	g_windowSettings.windowTitle = "Prog 4 Engine";
	g_windowSettings.dataPath = "../Data/";
	g_windowSettings.fps = 60;
	g_windowSettings.width = WINDOW_WIDTH;
	g_windowSettings.height = WINDOW_HEIGHT;

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