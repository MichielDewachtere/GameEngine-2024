#include <exception>
#include <iostream>

#ifdef _DEBUG
//#include <vld.h>
#endif 

#include <Minigin.h>
#include <SceneManager.h>
#include <ResourceManager.h>

#include "LabScene.h"
#include "Level01.h"
#include "LevelGenerator.h"
#include "Macros.h"
#include "TestSecondScene.h"

void load()
{
	using namespace dae;

	LevelGenerator::GetInstance().GenerateLevel();

	SceneManager::GetInstance().CreateScene(new Level01());
	SceneManager::GetInstance().CreateScene(new LabScene("labScene", "test"));
	SceneManager::GetInstance().CreateScene(new TestSecondScene("secondScene", "secondScene"));

	SceneManager::GetInstance().SetSceneActive("level01");
}

int main(int, char* [])
{
	dae::WindowSettings windowSettings;
	windowSettings.windowTitle = "Prog 4 Engine";
	windowSettings.dataPath = "../Data/";
	windowSettings.fps = 60;
	windowSettings.width = 224 * PIXEL_SCALE;
	windowSettings.height = 272 * PIXEL_SCALE;

	try
	{
		dae::Minigin engine(windowSettings);
		engine.Run(load);
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}