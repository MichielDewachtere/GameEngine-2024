#include "PlayerManager.h"

#include <algorithm>
#include <InputManager.h>

#include "Game.h"
#include "GameInfo.h"
#include "GameObject.h"
#include "InteractCommand.h"
#include "MoveCommand.h"
#include "Player.h"
#include "SceneManager.h"

void PlayerManager::Reset()
{
	std::ranges::for_each(m_pPlayers, [](PlayerInfo& p)
		{
			p.object = nullptr;
		});

	const auto v = dae::SceneManager::GetInstance().GetActiveScene().FindGameObjectsWithTag(Tags::game);
	v.front()->GetComponent<Game>()->gameEvent.AddObserver(this);
}

void PlayerManager::HandleEvent(GameEvents event)
{
	switch (event)
	{
	case GameEvents::started:
	case GameEvents::resumed:
	{
		std::ranges::for_each(m_pPlayers, [](const PlayerInfo& p)
			{
				p.object->GetComponent<Move>()->Enable();
			});
		break;
	}
	case GameEvents::finished:
	case GameEvents::paused:
	{
		std::ranges::for_each(m_pPlayers, [](const PlayerInfo& p)
			{
				p.object->GetComponent<Move>()->Disable();
			});
		break;
	}
	case GameEvents::reset:
	{
		std::ranges::for_each(m_pPlayers, [this](PlayerInfo& p)
			{
				p.object->GetComponent<Player>()->ReSpawn();

				const auto move = p.object->GetComponent<Move>();
				const auto pos = p.object->GetParent()->GetComponent<Maze>()->GetNearestFreePos(p.spawnPos);
				move->SetMazePos(pos);
			});
		break;
	}
	}
}

void PlayerManager::OnSubjectDestroy()
{
	auto v = dae::SceneManager::GetInstance().GetActiveScene().FindGameObjectsWithTag(Tags::game);
	if (v.empty() == false)
	{
		v.front()->GetComponent<Game>()->gameEvent.RemoveObserver(this);
	}
}

void PlayerManager::RegisterPlayer(const PlayerInfo info)
{
	m_pPlayers.push_back(info);
	++m_AmountOfPlayers;
}

bool PlayerManager::RequestPlayer() const
{
	int counter = 0;
	for (const auto& p : m_pPlayers)
	{
		counter += static_cast<int>(p.object != nullptr);
	}

	return counter < m_AmountOfPlayers;
}

void PlayerManager::AddPlayer(dae::GameObject* pPlayer, const glm::ivec2& playerSpawn)
{
	const auto map = dae::InputManager::GetInstance().GetActiveInputMap();
	for (auto& [object, spawnPos, useKeyboard, controllerId] : m_pPlayers)
	{
		if (object == nullptr)
		{
			object = pPlayer;
			spawnPos = playerSpawn;

			if (useKeyboard)
			{
				map->AddKeyboardAction<MoveCommand>(InputCommands::move_up, dae::KeyState::keyPressed, SDL_SCANCODE_UP, pPlayer, Direction::up);
				map->AddKeyboardAction<MoveCommand>(InputCommands::move_down, dae::KeyState::keyPressed, SDL_SCANCODE_DOWN, pPlayer, Direction::down);
				map->AddKeyboardAction<MoveCommand>(InputCommands::move_left, dae::KeyState::keyPressed, SDL_SCANCODE_LEFT, pPlayer, Direction::left);
				map->AddKeyboardAction<MoveCommand>(InputCommands::move_right, dae::KeyState::keyPressed, SDL_SCANCODE_RIGHT, pPlayer, Direction::right);

				map->AddKeyboardAction<InteractCommand>(InputCommands::interact, dae::KeyState::keyDown, SDL_SCANCODE_SPACE, pPlayer);
			}
			else
			{
				map->AddGamePadAction<MoveCommand>(controllerId, InputCommands::move_up, dae::KeyState::keyPressed, dae::GamePad::Button::dPadUp, pPlayer, Direction::up);
				map->AddGamePadAction<MoveCommand>(controllerId, InputCommands::move_down, dae::KeyState::keyPressed, dae::GamePad::Button::dPadDown, pPlayer, Direction::down);
				map->AddGamePadAction<MoveCommand>(controllerId, InputCommands::move_left, dae::KeyState::keyPressed, dae::GamePad::Button::dPadLeft, pPlayer, Direction::left);
				map->AddGamePadAction<MoveCommand>(controllerId, InputCommands::move_right, dae::KeyState::keyPressed, dae::GamePad::Button::dPadRight, pPlayer, Direction::right);

				map->AddGamePadAction<InteractCommand>(controllerId, InputCommands::interact, dae::KeyState::keyDown, dae::GamePad::Button::buttonDown, pPlayer);
			}
			break;
		}
	}
}