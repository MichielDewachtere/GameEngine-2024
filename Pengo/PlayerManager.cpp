#include "PlayerManager.h"

#include <InputManager.h>

#include "GameInfo.h"
#include "InteractCommand.h"
#include "MoveCommand.h"

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

void PlayerManager::AddPlayer(dae::GameObject* pPlayer)
{
	const auto map = dae::InputManager::GetInstance().GetActiveInputMap();
	for (auto& [object, useKeyboard, controllerId] : m_pPlayers)
	{
		if (object == nullptr)
		{
			object = pPlayer;
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