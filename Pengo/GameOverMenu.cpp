#include "GameOverMenu.h"

#include <TextureComponent.h>
#include <ResourceManager.h>
#include <TextComponent.h>

#include "Macros.h"
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
		auto pFont = real::ResourceManager::GetInstance().LoadFont(FONT_PATH, FONT_SIZE);

		textOne.GetTransform()->SetLocalPosition(m_Settings.width / 2.f, m_Settings.height / 2.f - 25.f);
		textOne.AddComponent<real::TextureComponent>();
		textOne.AddComponent<real::TextComponent>(" ", std::move(pFont))->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		textOne.AddComponent<TextFadeIn>("thanks for playing.");
	}
	{
		auto pFont = real::ResourceManager::GetInstance().LoadFont(FONT_PATH, FONT_SIZE);

		auto& textTwo = textOne.CreateGameObject();
		textTwo.SetIsActive(false, true);
		textTwo.GetTransform()->SetLocalPosition(0, 50);
		textTwo.AddComponent<real::TextureComponent>();
		textTwo.AddComponent<real::TextComponent>(" ", std::move(pFont))->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		textTwo.AddComponent<TextFadeIn>("try once more !");
	}
}