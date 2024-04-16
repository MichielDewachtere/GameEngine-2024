﻿#include "HUD.h"

#include <TextComponent.h>
#include <Colors.h>
#include <ResourceManager.h>
#include <SceneManager.h>
#include <TextureComponent.h>

#include "HealthDisplay.h"
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
	//InitEnemyDisplay();
	////	Add level (act) / 5
	//InitLevelDisplayTop();
	// Bottom:
	////	Add level (act) % 5
	//InitLevelDisplayBottom();

	real::SceneManager::GetInstance().loadScene.AddObserver(this);
	real::SceneManager::GetInstance().exitScene.AddObserver(this);
}

void HUD::HandleEvent(real::SceneEvents event, real::Scene* pScene)
{
	if (pScene->GetName().find("level") == std::string::npos)
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

void HUD::AddScore(ScoreEvents event, PlayerNumber p) const
{
	if (p == PlayerNumber::playerOne)
		m_pScoreDisplayPlayerOne->AddScore(event);
	if (p == PlayerNumber::playerTwo)
		m_pScoreDisplayPlayerTwo->AddScore(event);

	// TODO: Notify HighScore
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
	auto font = real::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

	auto& player = m_pUniqueHud->CreateGameObject();
	player.AddComponent<real::TextureComponent>();
	if (p == PlayerNumber::playerOne)
	{
		player.GetTransform()->SetLocalPosition(WALL_WIDTH * PIXEL_SCALE, 0);
		player.AddComponent<real::TextComponent>("P1", std::move(font), real::Colors::cyan);
	}
	else
	{
		player.GetTransform()->SetLocalPosition(WALL_WIDTH * PIXEL_SCALE + MAZE_WIDTH * BLOCK_SIZE * 2, 0);
		player.AddComponent<real::TextComponent>("P2", std::move(font), real::Colors::cyan);
	}

	font = real::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

	auto& scoreDisplay = player.CreateGameObject();
	scoreDisplay.GetTransform()->SetLocalPosition((MAZE_WIDTH - 1) * BLOCK_SIZE, 0);
	scoreDisplay.AddComponent<real::TextureComponent>();
	scoreDisplay.AddComponent<real::TextComponent>("0", std::move(font))->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::left);
	if (p == PlayerNumber::playerOne)
		m_pScoreDisplayPlayerOne = scoreDisplay.AddComponent<ScoreDisplay>();
	else
		m_pScoreDisplayPlayerTwo = scoreDisplay.AddComponent<ScoreDisplay>();
}

void HUD::InitHighScoreDisplay() const
{
	auto font = real::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

	auto& player = m_pUniqueHud->CreateGameObject();
	player.AddComponent<real::TextureComponent>();
	player.GetTransform()->SetLocalPosition(WALL_WIDTH * PIXEL_SCALE + MAZE_WIDTH * BLOCK_SIZE, 0);
	player.AddComponent<real::TextComponent>("HI", std::move(font), real::Colors::cyan);

	font = real::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

	auto& highScoreDisplay = player.CreateGameObject();
	highScoreDisplay.GetTransform()->SetLocalPosition((MAZE_WIDTH - 1) * BLOCK_SIZE, 0);
	highScoreDisplay.AddComponent<real::TextureComponent>();
	highScoreDisplay.AddComponent<real::TextComponent>("0", std::move(font))->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::left);
}

void HUD::InitLivesDisplay()
{
	auto& health = m_pUniqueHud->CreateGameObject();
	health.GetTransform()->SetLocalPosition(0, WALL_WIDTH * PIXEL_SCALE);
	m_pHealthDisplay = health.AddComponent<HealthDisplay>();

}
