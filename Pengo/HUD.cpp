#include "HUD.h"

#include <TextComponent.h>
#include <Colors.h>
#include <ResourceManager.h>
#include <SceneManager.h>
#include <TextureComponent.h>

#include "ScoreDisplay.h"

HUD::~HUD()
{
	dae::SceneManager::GetInstance().loadScene.RemoveObserver(this);
	dae::SceneManager::GetInstance().exitScene.RemoveObserver(this);
}

void HUD::Init()
{
	// TODO:
	InitHud();
	// TOP:
	//		Add Score player 1 AND 2
	InitScoreDisplay();
	////		Add High score
	//InitHighScoreDisplay();
	////		Add Lives
	//InitLivesDisplay();
	////		Amount of sno-bee eggs
	//InitEnemyDisplay();
	////		Add level (act) / 5
	//InitLevelDisplayTop();
	//// Bottom
	////		Add level (act) % 5
	//InitLevelDisplayBottom();

	dae::SceneManager::GetInstance().loadScene.AddObserver(this);
	dae::SceneManager::GetInstance().exitScene.AddObserver(this);
}

void HUD::HandleEvent(dae::SceneEvents event, dae::Scene* pScene)
{
	if (pScene->GetName().find("level") == std::string::npos)
		return;

	switch (event)
	{
		case dae::SceneEvents::exit:
		{
			m_pUniqueHud = pScene->GetUniqueGameObject(m_HudId);
			break;
		}
		case dae::SceneEvents::load:
		{
			pScene->AddGameObject(std::move(m_pUniqueHud));
			break;
		}
	}
}

void HUD::AddScore(ScoreEvents event) const
{
	m_pScoreDisplayPlayerOne->AddScore(event);
}

void HUD::InitHud()
{
	m_pUniqueHud = std::make_unique<dae::GameObject>(nullptr);
	m_HudId = m_pUniqueHud->GetId();
}

void HUD::InitScoreDisplay()
{
	auto font = dae::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

	auto& playerOne = m_pUniqueHud->CreateGameObject();
	playerOne.AddComponent<dae::TextureComponent>();
	playerOne.AddComponent<dae::TextComponent>("P1", std::move(font), dae::Colors::cyan);

	font = dae::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

	auto& scoreDisplay = playerOne.CreateGameObject();
	scoreDisplay.GetTransform()->SetLocalPosition(50, 0);
	scoreDisplay.AddComponent<dae::TextureComponent>();
	scoreDisplay.AddComponent<dae::TextComponent>("0", std::move(font));
	m_pScoreDisplayPlayerOne = scoreDisplay.AddComponent<ScoreDisplay>();
}
