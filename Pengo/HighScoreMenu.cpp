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
		auto& test = CreateGameObject();
		test.GetTransform()->SetLocalPosition(m_Settings.width / 2.f, 100);
		test.AddComponent<real::TextureComponent>();
		real::TextInfo info{};
		info.text = "enter your initials";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		info.color = real::Colors::yellow;
		info.horizontalAlignment = real::HorizontalTextAlignment::center;
		test.AddComponent<real::TextComponent>(std::move(info));
		test.AddComponent<RegisterHighScore>();
	}
	{
		constexpr float leaderBoardOffset = 104 * PIXEL_SCALE;
		auto& test = CreateGameObject();
		test.GetTransform()->SetLocalPosition(m_Settings.width / 2.f, leaderBoardOffset);
		test.AddComponent<LeaderBoard>();
	}
}
