#include "HighScoreMenu.h"

#include <TextComponent.h>
#include <TextureComponent.h>
#include <ResourceManager.h>

#include "Colors.h"
#include "LeaderBoard.h"
#include "RegisterHighScore.h"

HighScoreMenu::HighScoreMenu(std::string name, std::string inputMap, real::WindowSettings settings)
	: Scene(std::move(name), std::move(inputMap))
	, m_Settings(std::move(settings))
{
}

void HighScoreMenu::Load()
{
	{
		auto pFont = real::ResourceManager::GetInstance().LoadFont("pengo_arcade.ttf", 48);

		auto& test = CreateGameObject();
		test.GetTransform()->SetLocalPosition(m_Settings.width / 2.f, 100);
		test.AddComponent<real::TextureComponent>();
		const auto textComp = test.AddComponent<real::TextComponent>("enter your initials", std::move(pFont), real::Colors::yellow);
		textComp->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		test.AddComponent<RegisterHighScore>();
	}
	{
		//auto pFont = real::ResourceManager::GetInstance().LoadFont(FONT_PATH, 32);

		constexpr float leaderBoardOffset = 104 * PIXEL_SCALE;
		auto& test = CreateGameObject();
		test.GetTransform()->SetLocalPosition(m_Settings.width / 2.f, leaderBoardOffset);
		//test.AddComponent<real::TextureComponent>();
		//const auto textComp = test.AddComponent<real::TextComponent>("leaderboard", std::move(pFont), real::Colors::pink);
		//textComp->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		test.AddComponent<LeaderBoard>();
	}
}
