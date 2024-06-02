#include "GameOverMenu.h"

#include <TextureComponent.h>
#include <ResourceManager.h>
#include <TextComponent.h>
#include <InputManager.h>

#include "Colors.h"
#include "Macros.h"
#include "RestartCommand.h"
#include "TextFadeIn.h"

GameOverMenu::GameOverMenu(std::string name, std::string inputMap, real::WindowSettings settings)
	: Scene(std::move(name), std::move(inputMap))
	, m_Settings(std::move(settings))
{
}

void GameOverMenu::Load()
{
	auto& textOne = CreateGameObject();
	{
		textOne.GetTransform()->SetLocalPosition(m_Settings.width / 2.f, m_Settings.height / 2.f - 25.f);
		textOne.AddComponent<real::TextureComponent>();

		real::TextInfo info{};
		info.text = " ";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		info.horizontalAlignment = real::HorizontalTextAlignment::center;
		textOne.AddComponent<real::TextComponent>(std::move(info));
		textOne.AddComponent<TextFadeIn>("thanks for playing.");
	}
	auto& textTwo = textOne.CreateGameObject();
	{
		textTwo.SetIsActive(false, true);
		textTwo.GetTransform()->SetLocalPosition(0, 50);
		textTwo.AddComponent<real::TextureComponent>();

		real::TextInfo info{};
		info.text = " ";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		info.horizontalAlignment = real::HorizontalTextAlignment::center;
		textTwo.AddComponent<real::TextComponent>(std::move(info));
		textTwo.AddComponent<TextFadeIn>("try once more !");
	}
	{
		auto& restart = textTwo.CreateGameObject();
		restart.SetIsActive(false, true);
		restart.GetTransform()->SetLocalPosition(0, 100);
		restart.AddComponent<real::TextureComponent>();

		real::TextInfo info{};
		info.text = " ";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), 32);
		info.horizontalAlignment = real::HorizontalTextAlignment::center;
		info.color = real::Colors::dark_grey;
		restart.AddComponent<real::TextComponent>(std::move(info));
		restart.AddComponent<TextFadeIn>("- press space/a to restart -");
	}

	auto& input = real::InputManager::GetInstance();
	auto map = input.GetActiveInputMap();
	map->AddKeyboardAction<RestartCommand>(1, real::KeyState::keyUp, SDL_SCANCODE_SPACE);

	for (const auto& gamePads : input.GetGamePads())
	{
		map->AddGamePadAction<RestartCommand>(gamePads->GetIndex(), 0, real::KeyState::keyUp, real::GamePad::Button::buttonDown);
	}

}