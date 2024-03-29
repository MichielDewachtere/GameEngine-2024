#include <exception>
#include <iostream>

#ifdef _DEBUG
//#include <vld.h>
#endif 

#include <Minigin.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <InputManager.h>

#include "BonusTimeMenu.h"
#include "GameInfo.h"
#include "LabScene.h"
#include "Level.h"
#include "LevelGenerator.h"
#include "Macros.h"
#include "PlayerManager.h"
#include "TestSecondScene.h"

dae::WindowSettings g_windowSettings;

void load()
{
	using namespace dae;

	LevelGenerator::GetInstance().GenerateLevel();

	auto& input = dae::InputManager::GetInstance();
	input.AddInputMap(InputMaps::gameplay);
	input.EnableGamePadInput(true);
	input.SetInputMapActive(InputMaps::gameplay);

	const auto idcs = input.RegisterGamePads();
	if (idcs.empty())
	{
		PlayerManager::GetInstance().RegisterPlayer({ nullptr, {}, true, 255 });
	}
	else
	{
		for (const auto idx : idcs)
		{
			PlayerManager::GetInstance().RegisterPlayer({ nullptr, {}, false, idx });
		}
	}

	// TODO: Add Menu's
	SceneManager::GetInstance().CreateScene(new BonusTimeMenu(Scenes::bonus_menu, "none", g_windowSettings));

	SceneManager::GetInstance().CreateScene(new Level("level1", InputMaps::gameplay));
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

	SceneManager::GetInstance().CreateScene(new LabScene("labScene", "test"));
	SceneManager::GetInstance().CreateScene(new TestSecondScene("secondScene", "secondScene"));

	SceneManager::GetInstance().SetSceneActive("level1");
}

int main(int, char* [])
{
	g_windowSettings.windowTitle = "Prog 4 Engine";
	g_windowSettings.dataPath = "../Data/";
	g_windowSettings.fps = 60;
	g_windowSettings.width = 224 * PIXEL_SCALE;
	g_windowSettings.height = 280 * PIXEL_SCALE;

	try
	{
		dae::Minigin engine(g_windowSettings);
		engine.Run(load);
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}