#include "Game.h"

#include <glm/vec4.hpp>

#include <GameObject.h>
#include <GameTime.h>

#include "Colors.h"
#include "Macros.h"
#include "Renderer.h"

Game::Game(dae::GameObject* pOwner)
	: DrawableComponent(pOwner)
{
}

void Game::Update()
{
	if (m_GameFinished)
		return;

	auto dt = dae::GameTime::GetInstance().GetElapsed();

	if (m_AccuTime > m_StartTime)
	{
		m_GameTime += dt;

		if (m_GameStarted == false)
		{
			m_GameStarted = true;
			gameStarted.Notify(GameEvents::start);
		}
	}
	else
	{
		m_AccuTime += dt;
	}
}

void Game::Render()
{
	if (m_GameStarted == false && m_AccuTime < m_CurtainTime)
	{
		DrawCurtain();
	}
}

void Game::EndGame()
{
	m_GameFinished = true;
}

void Game::DrawCurtain() const
{
	const auto percentage = (m_CurtainTime - m_AccuTime) / m_CurtainTime;
	const auto pos = GetOwner()->GetTransform()->GetWorldPosition();

	const glm::vec4 rect = {
		pos.x + WALL_WIDTH * PIXEL_SCALE,
		pos.y + WALL_WIDTH * PIXEL_SCALE,
		MAZE_WIDTH * PIXEL_SCALE * BLOCK_SIZE,
		MAZE_HEIGHT * PIXEL_SCALE * BLOCK_SIZE * percentage
	};

	dae::Renderer::GetInstance().RenderRectangle(rect, true, dae::Colors::black);
}
