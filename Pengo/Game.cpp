#include "Game.h"

#include <glm/vec4.hpp>

#include <GameObject.h>
#include <GameTime.h>
#include <TextureComponent.h>
#include <TextComponent.h>
#include <ResourceManager.h>

#include "Colors.h"
#include "GameInfo.h"
#include "Macros.h"
#include "Renderer.h"
#include "SceneManager.h"

Game::Game(dae::GameObject* pOwner)
	: DrawableComponent(pOwner)
{
	m_GameTime = 0;
	m_CurrentLevel %= 16;
	++m_CurrentLevel;

	auto pFont = dae::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);
	m_pPauseText = &dae::SceneManager::GetInstance().GetActiveScene().CreateGameObject();

	m_pPauseText->GetTransform()->SetLocalPosition(
		(MAZE_WIDTH * PIXEL_SCALE * BLOCK_SIZE + WALL_WIDTH * PIXEL_SCALE * 2) / 2.f,
		(MAZE_HEIGHT * PIXEL_SCALE * BLOCK_SIZE + WALL_WIDTH * PIXEL_SCALE * 2) / 2.f + 100.f
	);

	m_pPauseText->AddComponent<dae::TextureComponent>();
	m_pPauseText->AddComponent<dae::TextComponent>("Ready ?", std::move(pFont))
		->SetHorizontalAlignment(dae::TextComponent::HorizontalAlignment::center);
}

void Game::Update()
{
	const auto dt = dae::GameTime::GetInstance().GetElapsed();

	switch (m_CurrentState)
	{
	case GameState::start:
	{
		m_AccuTime += dt;

		m_pPauseText->SetIsActive(false, true);

		if (m_AccuTime > m_StartTime)
		{
			gameEvent.Notify(GameEvents::started);
			m_CurrentState = GameState::running;
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
			m_AccuTime = 0;
			m_pPauseText->SetIsActive(false, true);
			m_CurrentState = GameState::resume;

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
	case GameState::finished:
	{
		m_AccuTime += dt;
		if (m_AccuTime > m_CurtainTime)
		{
			dae::SceneManager::GetInstance().SetSceneActive(Scenes::bonus_menu);
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
	case GameState::finished:
	{
		DrawCurtain(false, m_CurtainTime);
		break;
	}
	}
}

void Game::EndGame(bool won)
{
	if (won)
	{
		m_CurrentState = GameState::finished;
		gameEvent.Notify(GameEvents::finished);
	}
	else
	{
		gameEvent.Notify(GameEvents::paused);
		m_CurrentState = GameState::paused;
	}

	m_AccuTime = 0;
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

	dae::Renderer::GetInstance().RenderRectangle(rect, true, dae::Colors::black);
}
