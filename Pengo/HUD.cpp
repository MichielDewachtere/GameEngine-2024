#include "HUD.h"

#include <TextComponent.h>
#include <Colors.h>
#include <ResourceManager.h>
#include <SceneManager.h>
#include <TextureComponent.h>

#include "EggCounter.h"
#include "GameInfo.h"
#include "HealthDisplay.h"
#include "HighScoreDisplay.h"
#include "LevelDisplayBottom.h"
#include "LevelDisplayTop.h"
#include "ScoreDisplay.h"
#include "Macros.h"
#include "Player.h"

HUD::~HUD()
{
	real::SceneManager::GetInstance().loadScene.RemoveObserver(this);
	real::SceneManager::GetInstance().exitScene.RemoveObserver(this);
}

void HUD::Init()
{
	// TODO:
	InitHud();
	// TOP:
	//		Add Score player 1 AND 2
	InitScoreDisplay(PlayerNumber::playerOne);
	InitScoreDisplay(PlayerNumber::playerTwo);
	////	Add High score
	InitHighScoreDisplay();
	////	Add Lives
	InitLivesDisplay();
	////	Amount of sno-bee eggs
	InitEnemyDisplay();
	////	Add level (act) / 5
	InitLevelDisplayTop();
	// Bottom:
	////	Add level (act) % 5
	InitLevelDisplayBottom();

	real::SceneManager::GetInstance().loadScene.AddObserver(this);
	real::SceneManager::GetInstance().exitScene.AddObserver(this);
}

void HUD::HandleEvent(real::SceneEvents event, real::Scene* pScene)
{
	if (pScene->GetName().find("level") == std::string::npos 
		&& pScene->GetName() != Scenes::bonus_menu)
		return;

	switch (event)
	{
		case real::SceneEvents::exit:
		{
			m_pUniqueHud = pScene->GetUniqueGameObject(m_HudId);
			break;
		}
		case real::SceneEvents::load:
		{
			pScene->AddGameObject(std::move(m_pUniqueHud));
			break;
		}
	}
}

void HUD::Reset() const
{
	m_pScoreDisplayPlayerOne->Reset();
	m_pScoreDisplayPlayerTwo->Reset();

	m_pHealthDisplay->Reset();

	m_pLevelDisplayBot->Reset();
	m_pLevelDisplayTop->Reset();
}

void HUD::AddScore(ScoreEvents event, PlayerNumber p) const
{
	if (p == PlayerNumber::playerOne)
		m_pScoreDisplayPlayerOne->AddScore(event);
	if (p == PlayerNumber::playerTwo)
		m_pScoreDisplayPlayerTwo->AddScore(event);

	if (m_pScoreDisplayPlayerTwo != nullptr)
		m_pHighScoreDisplay->CheckForHighScore(m_pScoreDisplayPlayerOne->GetScore() + m_pScoreDisplayPlayerTwo->GetScore());
	else
		m_pHighScoreDisplay->CheckForHighScore(m_pScoreDisplayPlayerOne->GetScore());
}

int HUD::GetTotalScore()
{
	if (m_pScoreDisplayPlayerTwo != nullptr)
		return m_pScoreDisplayPlayerOne->GetScore() + m_pScoreDisplayPlayerTwo->GetScore();

	return m_pScoreDisplayPlayerOne->GetScore();
}

void HUD::AddLife() const
{
	m_pHealthDisplay->AddLife();
}

void HUD::RemoveLife() const
{
	m_pHealthDisplay->RemoveLife();
}

void HUD::InitHud()
{
	m_pUniqueHud = std::make_unique<real::GameObject>(nullptr);
	m_HudId = m_pUniqueHud->GetId();
}

void HUD::InitScoreDisplay(PlayerNumber p)
{
	auto& player = m_pUniqueHud->CreateGameObject();
	player.AddComponent<real::TextureComponent>();
	if (p == PlayerNumber::playerOne)
	{
		player.GetTransform()->SetLocalPosition(WALL_WIDTH * PIXEL_SCALE, 0);

		real::TextInfo info{};
		info.text = "P1";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		info.color = real::Colors::cyan;
		player.AddComponent<real::TextComponent>(std::move(info));
	}
	else
	{
		player.GetTransform()->SetLocalPosition(WALL_WIDTH * PIXEL_SCALE + MAZE_WIDTH * BLOCK_SIZE * 2, 0);

		real::TextInfo info{};
		info.text = "P2";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		info.color = real::Colors::cyan;
		player.AddComponent<real::TextComponent>(std::move(info));
	}

	auto& scoreDisplay = player.CreateGameObject();
	scoreDisplay.GetTransform()->SetLocalPosition((MAZE_WIDTH - 1) * BLOCK_SIZE, 0);
	scoreDisplay.AddComponent<real::TextureComponent>();

	real::TextInfo info{};
	info.text = "0";
	info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
	info.horizontalAlignment = real::HorizontalTextAlignment::left;
	scoreDisplay.AddComponent<real::TextComponent>(std::move(info));
	if (p == PlayerNumber::playerOne)
		m_pScoreDisplayPlayerOne = scoreDisplay.AddComponent<ScoreDisplay>();
	else
		m_pScoreDisplayPlayerTwo = scoreDisplay.AddComponent<ScoreDisplay>();
}

void HUD::InitHighScoreDisplay()
{
	auto& player = m_pUniqueHud->CreateGameObject();
	player.AddComponent<real::TextureComponent>();
	player.GetTransform()->SetLocalPosition(WALL_WIDTH * PIXEL_SCALE + MAZE_WIDTH * BLOCK_SIZE, 0);

	{
		real::TextInfo info{};
		info.text = "HI";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		info.color = real::Colors::cyan;
		player.AddComponent<real::TextComponent>(std::move(info));
	}

	auto& highScoreDisplay = player.CreateGameObject();
	highScoreDisplay.GetTransform()->SetLocalPosition((MAZE_WIDTH - 1) * BLOCK_SIZE, 0);
	highScoreDisplay.AddComponent<real::TextureComponent>();

	{
		real::TextInfo info{};
		info.text = "0";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		info.horizontalAlignment = real::HorizontalTextAlignment::left;
		highScoreDisplay.AddComponent<real::TextComponent>(std::move(info));
	}
	m_pHighScoreDisplay = highScoreDisplay.AddComponent<HighScoreDisplay>();
}

void HUD::InitLivesDisplay()
{
	auto& health = m_pUniqueHud->CreateGameObject();
	health.GetTransform()->SetLocalPosition(0, WALL_WIDTH * PIXEL_SCALE);
	m_pHealthDisplay = health.AddComponent<HealthDisplay>();

}

void HUD::InitEnemyDisplay() const
{
	auto& enemies = m_pUniqueHud->CreateGameObject();
	enemies.GetTransform()->SetLocalPosition(((MAZE_WIDTH + 3) * BLOCK_SIZE / 3 * PIXEL_SCALE), WALL_WIDTH * PIXEL_SCALE * 2);
	enemies.AddComponent<EggCounter>();
}

void HUD::InitLevelDisplayTop()
{
	auto& levelDisplay = m_pUniqueHud->CreateGameObject();
	levelDisplay.GetTransform()->SetLocalPosition((MAZE_WIDTH + 1) * BLOCK_SIZE * PIXEL_SCALE, WALL_WIDTH * PIXEL_SCALE);
	m_pLevelDisplayTop = levelDisplay.AddComponent<LevelDisplayTop>();
}

void HUD::InitLevelDisplayBottom()
{
	auto& levelDisplay = m_pUniqueHud->CreateGameObject();
	levelDisplay.GetTransform()->SetLocalPosition(0, ((MAZE_HEIGHT + 2) * BLOCK_SIZE + WALL_WIDTH) * PIXEL_SCALE);
	levelDisplay.AddComponent<real::TextureComponent>();

	real::TextInfo info{};
	info.text = "act 1";
	info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
	info.verticalAlignment = real::VerticalTextAlignment::down;
	levelDisplay.AddComponent<real::TextComponent>(std::move(info));
	m_pLevelDisplayBot = levelDisplay.AddComponent<LevelDisplayBottom>();
}
