﻿#include "BonusTimeMenu.h"

#include <memory>

#include <TextureComponent.h>
#include <TextComponent.h>
#include <ResourceManager.h>

#include "BonusTime.h"
#include "Colors.h"
#include "Macros.h"

BonusTimeMenu::BonusTimeMenu(std::string name, std::string inputMap, dae::WindowSettings settings)
	: Scene(std::move(name), std::move(inputMap))
	, m_Settings(std::move(settings))
{
}

void BonusTimeMenu::Load()
{

	auto& bonusTime = CreateGameObject();
	{
		auto pFont = dae::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

		bonusTime.GetTransform()->SetLocalPosition({ static_cast<float>(m_Settings.width) / 2.f, BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE });
		bonusTime.AddComponent<BonusTime>();
		bonusTime.AddComponent<dae::TextureComponent>();
		const auto textComponent = bonusTime.AddComponent<dae::TextComponent>(" ", std::move(pFont));
		textComponent->SetHorizontalAlignment(dae::TextComponent::HorizontalAlignment::center);
	}
	{
		auto pFont = dae::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

		auto& time = bonusTime.CreateGameObject();
		time.GetTransform()->SetLocalPosition({ 0,0 });
		time.AddComponent<dae::TextureComponent>();
		const auto textComponent = time.AddComponent<dae::TextComponent>("GAME TIME    MIN.   SEC.", std::move(pFont));
		textComponent->SetColor(dae::Colors::yellow);
		textComponent->SetHorizontalAlignment(dae::TextComponent::HorizontalAlignment::center);
	}
	{
		WriteLine(bonusTime, 0, "FROM 00 TO 19 .5000 PTS.");
		WriteLine(bonusTime, 1, "FROM 20 TO 29 .2000 PTS.");
		WriteLine(bonusTime, 2, "FROM 30 TO 39 .1000 PTS.");
		WriteLine(bonusTime, 3, "FROM 40 TO 49 ..500 PTS.");
		WriteLine(bonusTime, 4, "FROM 50 TO 59 ...10 PTS.");
		WriteLine(bonusTime, 5, "60 AND OVER   .NO BONUS.");
	}
}

void BonusTimeMenu::WriteLine(dae::GameObject& go, int i, std::string text) const
{
	auto pFont = dae::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

	auto& line = go.CreateGameObject();
	line.GetTransform()->SetLocalPosition({ 0, 50 + i * 35 });
	line.AddComponent<dae::TextureComponent>();

	const auto textComponent = line.AddComponent<dae::TextComponent>(text, std::move(pFont));
	textComponent->SetColor(dae::Colors::cyan);

	textComponent->SetHorizontalAlignment(dae::TextComponent::HorizontalAlignment::center);
}