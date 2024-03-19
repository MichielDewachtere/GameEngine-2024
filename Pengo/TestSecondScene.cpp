#include "TestSecondScene.h"

#include <InputManager.h>

#include "LoadSceneCommand.h"

TestSecondScene::TestSecondScene(std::string name, std::string inputMap)
	: Scene(std::move(name), std::move(inputMap))
{
}

void TestSecondScene::Load()
{
	using namespace dae;

	auto& input = InputManager::GetInstance();
	const auto map = input.AddInputMap("secondScene");

	map->AddKeyboardAction<dae::TestCommand>(0, KeyState::keyDown, SDL_SCANCODE_SPACE);
	map->AddKeyboardAction<LoadSceneCommand>(1, KeyState::keyDown, SDL_SCANCODE_RETURN, "labScene");

}
