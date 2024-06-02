#include "Game.h"

#include <glm/vec4.hpp>
#include <imgui.h>

#include <GameObject.h>
#include <GameTime.h>
#include <TextureComponent.h>
#include <TextComponent.h>
#include <ResourceManager.h>

#include "Colors.h"
#include "GameInfo.h"
#include "HUD.h"
#include "Macros.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "HighScoreDisplay.h"
#include "Locator.h"

Game::Game(real::GameObject* pOwner)
	: DrawableComponent(pOwner)
{
	m_GameTime = 0;
	m_CurrentLevel %= 16;
	++m_CurrentLevel;

	m_pPauseText = &real::SceneManager::GetInstance().GetActiveScene().CreateGameObject();

	m_pPauseText->GetTransform()->SetLocalPosition(
		(MAZE_WIDTH * PIXEL_SCALE * BLOCK_SIZE + WALL_WIDTH * PIXEL_SCALE * 2) / 2.f,
		(MAZE_HEIGHT * PIXEL_SCALE * BLOCK_SIZE + WALL_WIDTH * PIXEL_SCALE * 2) / 2.f + 100.f
	);

	m_pPauseText->AddComponent<real::TextureComponent>();

	real::TextInfo info{};
	info.text = "ready ?";
	info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
	info.horizontalAlignment = real::HorizontalTextAlignment::center;
	m_pPauseText->AddComponent<real::TextComponent>(std::move(info));
}

void Game::Start()
{
	real::Locator::GetAudioSystem().Play(Sounds::act_start);
}

void Game::Update()
{
	const auto dt = real::GameTime::GetInstance().GetElapsed();

	switch (m_CurrentState)
	{
	case GameState::start:
	{
		m_AccuTime += dt;

		m_pPauseText->SetIsActive(false, true);

		if (m_AccuTime > m_StartTime)
		{
			real::Locator::GetAudioSystem().Play(Sounds::popcorn);
			HUD::GetInstance().RemoveLife();
			gameEvent.Notify(GameEvents::started);
			m_CurrentState = GameState::running;
			m_AccuTime = 0;
		}
		break;
	}
	case GameState::running:
	{
		m_GameTime += dt;
		break;
	}
	case GameState::paused:
	{
		m_AccuTime += dt;

		if (m_AccuTime > m_PauseTime + m_PauseCurtainTime)
		{
			real::Locator::GetAudioSystem().Stop(Sounds::popcorn.channel);
			real::Locator::GetAudioSystem().Play(Sounds::popcorn);

			m_pPauseText->SetIsActive(false, true);
			m_CurrentState = GameState::resume;
			m_AccuTime = 0;
			break;
		}
		if (m_AccuTime > m_PauseCurtainTime && m_pPauseText->IsActive() == false)
		{
			gameEvent.Notify(GameEvents::reset);
			m_pPauseText->SetIsActive(true, true);
		}
		break;
	}
	case GameState::resume:
	{
		m_AccuTime += dt;

		if (m_AccuTime > m_PauseCurtainTime)
		{
			gameEvent.Notify(GameEvents::resumed);
			m_CurrentState = GameState::running;
			m_AccuTime = 0;
		}
		break;
	}
	case GameState::actFinished:
	{
		m_AccuTime += dt;
		if (m_AccuTime > m_CurtainTime)
		{
			real::SceneManager::GetInstance().SetSceneActive(Scenes::bonus_menu);
			m_AccuTime = 0;
		}
		break;
	}
	case GameState::gameFinished:
	{
		m_AccuTime += dt;
		if (m_AccuTime > m_CurtainTime)
		{
			if (HighScoreDisplay::IsTopFive(HUD::GetInstance().GetTotalScore()))
				real::SceneManager::GetInstance().SetSceneActive(Scenes::high_score_menu);
			else
				real::SceneManager::GetInstance().SetSceneActive(Scenes::game_over_menu);
		}
		break;
	}
	}
}

void Game::Render()
{
	switch (m_CurrentState)
	{
	case GameState::start:
	{
		if (m_AccuTime < m_CurtainTime)
			DrawCurtain(true, m_CurtainTime);
		break;
	}
	case GameState::paused:
	{
		DrawCurtain(false, m_PauseCurtainTime);
		break;
	}
	case GameState::resume:
	{
		if (m_AccuTime < m_PauseCurtainTime)
		{
			DrawCurtain(true, m_PauseCurtainTime);
		}
		break;
	}
	case GameState::gameFinished:
	case GameState::actFinished:
	{
		DrawCurtain(false, m_CurtainTime);
		break;
	}
	case GameState::running: break;
	}
}

void Game::OnGui()
{
	bool open = true;
	ImGui::SetNextWindowSize(ImVec2(150, 50));
	ImGui::Begin("game time", &open);
	{
		ImGui::Text(std::to_string(m_GameTime).c_str());
	}
	ImGui::End();
}

void Game::EndAct(bool won)
{
	if (m_CurrentState == GameState::gameFinished)
		return;

	if (won)
	{
		real::Locator::GetAudioSystem().Stop(Sounds::act_clear.channel);
		real::Locator::GetAudioSystem().Play(Sounds::act_clear);

		HUD::GetInstance().AddLife();
		m_CurrentState = GameState::actFinished;
		gameEvent.Notify(GameEvents::finished);
	}
	else
	{
		real::Locator::GetAudioSystem().Stop(Sounds::killed.channel);
		real::Locator::GetAudioSystem().Play(Sounds::killed);

		gameEvent.Notify(GameEvents::paused);
		m_CurrentState = GameState::paused;
		HUD::GetInstance().RemoveLife();
	}

	m_AccuTime = 0;
}

void Game::EndGame()
{
	m_CurrentState = GameState::gameFinished;
	std::cout << "Game Ended\n";
}

void Game::Reset()
{
	m_IsPvP = false;
	m_CurrentLevel = 0;
	m_GameTime = 0;
}

void Game::DrawCurtain(bool open, float curtainTime) const
{
	float percentage;
	if (open)
		percentage = (curtainTime - m_AccuTime) / curtainTime;
	else
		percentage = m_AccuTime / curtainTime;

	const auto pos = GetOwner()->GetTransform()->GetWorldPosition();

	const glm::vec4 rect = {
		pos.x ,
		pos.y,
		MAZE_WIDTH * PIXEL_SCALE * BLOCK_SIZE + WALL_WIDTH * PIXEL_SCALE * 2,
		(MAZE_HEIGHT * PIXEL_SCALE * BLOCK_SIZE + WALL_WIDTH * PIXEL_SCALE * 2) * percentage
	};

	real::Renderer::GetInstance().RenderRectangle(rect, true, real::Colors::black);
}
