#include "BonusTime.h"

#include <GameTime.h>
#include <GameObject.h>
#include <Colors.h>
#include <SceneManager.h>
#include <TextComponent.h>

#include "Game.h"
#include "HUD.h"
#include "Player.h"
#include "PlayerManager.h"

BonusTime::BonusTime(real::GameObject* pOwner)
	: Component(pOwner)
{
}

void BonusTime::Update()
{
	const auto dt = real::GameTime::GetInstance().GetElapsed();
	m_AccuTime += dt;

	constexpr float timeToShowTime{ 0.5f }, timeToShowBonus{ 1.f }, lifeTime{ 3.f };

	if (m_AccuTime > lifeTime)
	{
		const int nextLevel = Game::GetCurrentLevel() + 1;
		real::SceneManager::GetInstance().SetSceneActive("level" + std::to_string(nextLevel));
		return;
	}
	if (m_BonusShown == false 
		&& m_AccuTime > timeToShowBonus)
	{
		m_BonusShown = true;

		const int gameTime = static_cast<int>(Game::GetGameTime());
		for (const auto& [bonusIdx, time, bonus] : m_BonusToTime)
		{
			if (gameTime >= time.first && gameTime <= time.second)
			{
				GetOwner()->GetChildAt(bonusIdx)->GetComponent<real::TextComponent>()->SetColor(real::Colors::yellow);
				if (PlayerManager::GetInstance().GetAmountOfPlayers() <= 1)
					HUD::GetInstance().AddScore(bonus, PlayerNumber::playerOne);
				else if (PlayerManager::GetInstance().GetAmountOfPlayers() == 2)
					HUD::GetInstance().AddScore(bonus, PlayerNumber::playerTwo);
				break;
			}
		}

		return;
	}
	if (m_TimeShown == false
		&& m_AccuTime > timeToShowTime)
	{
		m_TimeShown = true;

		const auto gameTime = Game::GetGameTime();

		const auto seconds = static_cast<int>(gameTime) % 60;
		const auto minutes = static_cast<int>(gameTime / 60.f);

		const auto textComponent = GetOwner()->GetComponent<real::TextComponent>();
		const auto text = "           " + std::to_string(minutes) + "     " + std::to_string(seconds) + "     ";
		textComponent->SetText(text);
	}
}
