#include "GameOverMenu.h"

#include <TextureComponent.h>
#include <ResourceManager.h>
#include <TextComponent.h>

GameOverMenu::GameOverMenu(std::string name, std::string inputMap)
	: Scene(std::move(name), std::move(inputMap))
{
}

void GameOverMenu::Load()
{
	auto pFont = real::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

	auto& test = CreateGameObject();
	test.AddComponent<real::TextureComponent>();
	test.AddComponent<real::TextComponent>("End Screen", std::move(pFont));
}