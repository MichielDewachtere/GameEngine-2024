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

	const auto v = real::SceneManager::GetInstance().GetActiveScene().FindGameObjectsWithTag(Tags::game);
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
	auto v = real::SceneManager::GetInstance().GetActiveScene().FindGameObjectsWithTag(Tags::game);
	if (v.empty() == false)
	{
		v.front()->GetComponent<Game>()->gameEvent.RemoveObserver(this);
	}
}

void PlayerManager::SetAmountOfPlayers(int amount, bool isPvp)
{
	for (int i = 0; i < amount; ++i)
	{
		PlayerInfo info{};
		info.color = GetRandomColor();
		info.isEnemy = isPvp && i == 1 ? true : false;

		m_pPlayers.push_back(info);
	}

	m_AmountOfPlayers = static_cast<uint8_t>(amount);
}

void PlayerManager::SetPlayerInput(int player, bool keyboard, uint8_t controllerId)
{
	m_pPlayers[player - 1].useKeyboard = keyboard;
	m_pPlayers[player - 1].controllerId = controllerId;
}

void PlayerManager::SetObjectAndPosition(int player, real::GameObject* pPlayer, const glm::ivec2& spawnPos)
{
	const auto map = real::InputManager::GetInstance().GetActiveInputMap();
	m_pPlayers[player - 1].object = pPlayer;
	m_pPlayers[player - 1].spawnPos = spawnPos;

	if (m_pPlayers[player - 1].useKeyboard)
	{
		map->AddKeyboardAction<MoveCommand>(InputCommands::move_up, real::KeyState::keyPressed, SDL_SCANCODE_UP, pPlayer, Direction::up);
		map->AddKeyboardAction<MoveCommand>(InputCommands::move_down, real::KeyState::keyPressed, SDL_SCANCODE_DOWN, pPlayer, Direction::down);
		map->AddKeyboardAction<MoveCommand>(InputCommands::move_left, real::KeyState::keyPressed, SDL_SCANCODE_LEFT, pPlayer, Direction::left);
		map->AddKeyboardAction<MoveCommand>(InputCommands::move_right, real::KeyState::keyPressed, SDL_SCANCODE_RIGHT, pPlayer, Direction::right);

		map->AddKeyboardAction<InteractCommand>(InputCommands::interact, real::KeyState::keyDown, SDL_SCANCODE_SPACE, pPlayer);
	}
	else
	{
		map->AddGamePadAction<MoveCommand>(m_pPlayers[player - 1].controllerId, InputCommands::move_up, real::KeyState::keyPressed, real::GamePad::Button::dPadUp, pPlayer, Direction::up);
		map->AddGamePadAction<MoveCommand>(m_pPlayers[player - 1].controllerId, InputCommands::move_down, real::KeyState::keyPressed, real::GamePad::Button::dPadDown, pPlayer, Direction::down);
		map->AddGamePadAction<MoveCommand>(m_pPlayers[player - 1].controllerId, InputCommands::move_left, real::KeyState::keyPressed, real::GamePad::Button::dPadLeft, pPlayer, Direction::left);
		map->AddGamePadAction<MoveCommand>(m_pPlayers[player - 1].controllerId, InputCommands::move_right, real::KeyState::keyPressed, real::GamePad::Button::dPadRight, pPlayer, Direction::right);

		map->AddGamePadAction<InteractCommand>(m_pPlayers[player - 1].controllerId, InputCommands::interact, real::KeyState::keyDown, real::GamePad::Button::buttonDown, pPlayer);
	}
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

uint8_t PlayerManager::GetAmountOfActivePlayers() const
{
	uint8_t counter = 0;
	for (const auto & pPlayer : m_pPlayers)
	{
		if (pPlayer.object->IsActive())
			++counter;
	}

	return counter;				
}

PlayerInfo PlayerManager::GetPlayerInfo(int player) const
{
	return m_pPlayers[player - 1];
}

ECharacterColors PlayerManager::GetRandomColor()
{
	ECharacterColors color;

	do
	{
		color = static_cast<ECharacterColors>(rand() % static_cast<uint8_t>(ECharacterColors::amountOfColors));
	}
	while (std::ranges::find_if(m_pPlayers, [color](const PlayerInfo& info) { return info.color == color; }) 
		!= m_pPlayers.end());

	return color;
}
