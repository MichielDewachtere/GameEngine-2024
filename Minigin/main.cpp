#include "stdafx.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "TrashTheCache.h"
#include "LabScene.h"
#include "TestSecondScene.h"

void load()
{
	using namespace dae;

	SceneManager::GetInstance().CreateScene(new LabScene("labScene", "test"));
	SceneManager::GetInstance().CreateScene(new TestSecondScene("secondScene", "secondScene"));

	SceneManager::GetInstance().SetSceneActive("labScene");
}

int main(int, char* [])
{
	dae::Settings settings;
	settings.windowTitle = "Prog 4 Engine";
	settings.dataPath = "../Data/";
	settings.fps = 60;
	settings.width = 640;
	settings.height = 480;

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