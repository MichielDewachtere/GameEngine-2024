#include <exception>
#include <iostream>

#include <Minigin.h>
#include <SceneManager.h>
#include <ResourceManager.h>

#include "LabScene.h"
#include "Level01.h"
#include "Macros.h"
#include "TestSecondScene.h"

void load()
{
	using namespace dae;

	SceneManager::GetInstance().CreateScene(new Level01());
	SceneManager::GetInstance().CreateScene(new LabScene("labScene", "test"));
	SceneManager::GetInstance().CreateScene(new TestSecondScene("secondScene", "secondScene"));

	SceneManager::GetInstance().SetSceneActive("level01");
}

int main(int, char* [])
{
	dae::Settings settings;
	settings.windowTitle = "Prog 4 Engine";
	settings.dataPath = "../Data/";
	settings.fps = 60;
	settings.width = 224 * PIXEL_SCALE;
	settings.height = 228 * PIXEL_SCALE;

	try
	{
		dae::Minigin engine(settings);
		engine.Run(load);
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}