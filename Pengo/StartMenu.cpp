#include "StartMenu.h"

#include <ResourceManager.h>
#include <InputManager.h>
#include <TextComponent.h>
#include <TextureComponent.h>
#include <Locator.h>
#include <Colors.h>

#include "FlickerText.h"
#include "GameInfo.h"
#include "Macros.h"
#include "SelectMode.h"
#include "StartScreen.h"

StartMenu::StartMenu(std::string name, std::string inputMap, real::WindowSettings settings)
	: Scene(std::move(name), std::move(inputMap))
	, m_Settings(std::move(settings))
{
}

void StartMenu::Load()
{
	real::Locator::GetAudioSystem().Play(Sounds::game_music);

	auto& startScreen = CreateGameObject("start-screen");
	{
		auto pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		startScreen.GetTransform()->SetLocalPosition(m_Settings.width / 2.f, 100);
		startScreen.AddComponent<real::TextureComponent>();
		startScreen.AddComponent<real::TextComponent>("Pengo", std::move(pFont))->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		startScreen.AddComponent<StartScreen>();
	}

	auto& mode = startScreen.CreateGameObject("select-mode");
	{
		auto pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		mode.GetTransform()->SetLocalPosition(0, 100);
		mode.AddComponent<real::TextureComponent>();

		const auto textComponent = mode.AddComponent<real::TextComponent>("mode", std::move(pFont));
		textComponent->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		textComponent->SetColor(real::Colors::red);

		mode.AddComponent<SelectMode>();
	}

	auto& start = startScreen.CreateGameObject("start-button");
	{
		auto pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), 64);
		start.GetTransform()->SetLocalPosition(0, 600);
		start.AddComponent<real::TextureComponent>();

		const auto textComponent = start.AddComponent<real::TextComponent>("- start -", std::move(pFont));
		textComponent->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		textComponent->SetColor(real::Colors::grey);

		start.AddComponent<FlickerText>(real::Colors::yellow, 0.5f)->Disable();
	}
}