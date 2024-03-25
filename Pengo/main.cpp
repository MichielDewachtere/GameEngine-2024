#include <exception>
#include <iostream>

#include <Minigin.h>
#include <SceneManager.h>
#include <ResourceManager.h>

#include "LabScene.h"
#include "Level01.h"
#include "Macros.h"
#include "TestSecondScene.h"

dae::WindowSettings g_windowSettings;

void load()
{
	using namespace dae;

	SceneManager::GetInstance().CreateScene(new Level01(g_windowSettings));
	SceneManager::GetInstance().CreateScene(new LabScene("labScene", "test"));
	SceneManager::GetInstance().CreateScene(new TestSecondScene("secondScene", "secondScene"));

	SceneManager::GetInstance().SetSceneActive("level01");
}

int main(int, char* [])
{
	g_windowSettings.windowTitle = "Prog 4 Engine";
	g_windowSettings.dataPath = "../Data/";
	g_windowSettings.fps = 60;
	g_windowSettings.width = 224 * PIXEL_SCALE;
	g_windowSettings.height = 272 * PIXEL_SCALE;

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