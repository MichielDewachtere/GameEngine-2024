// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
// ReSharper disable CppIncompleteSwitchStatement
// ReSharper disable CppClangTidyClangDiagnosticSwitch

#include "StartScreen.h"

#include <InputManager.h>
#include <TextureComponent.h>
#include <ResourceManager.h>
#include <TextComponent.h>
#include <Colors.h>
#include <GameObject.h>
#include <GameTime.h>

#include "FlickerText.h"
#include "Game.h"
#include "SelectMode.h"
#include "PlayerJoinCommand.h"
#include "GameInfo.h"
#include "Macros.h"
#include "PlayerManager.h"
#include "StartGameCommand.h"

StartScreen::StartScreen(real::GameObject* pOwner)
	: Component(pOwner)
{
}

void StartScreen::ModeSelected(Modes mode)
{
	m_CurrentState = State::selectPlayers;
	bool isPvp = false;

	switch (mode)
	{
		case Modes::singlePlayer:
		{
			m_AmountOfPlayersToRegister = 1;
			AddPlayerText(0, false, 1);
			break;
		}
		case Modes::coOp:
		{
			m_AmountOfPlayersToRegister = 2;
			AddPlayerText(-1, false, 1);
			AddPlayerText(1, false, 2);
			break;
		}
		case Modes::pvp:
		{
			m_AmountOfPlayersToRegister = 2;
			AddPlayerText(-1, false, 1);
			AddPlayerText(1, true, 2);
			isPvp = true;
			break;
		}
	}

	const auto& input = real::InputManager::GetInstance();
	const auto map = input.GetActiveInputMap();

	for (const auto& gamePads : input.GetGamePads())
	{
		map->AddGamePadAction<PlayerJoinCommand>(gamePads->GetIndex(), InputCommands::player_join, real::KeyState::keyDown,
			real::GamePad::Button::buttonDown, GetOwner(), m_AmountOfPlayersToRegister, isPvp);
	}

	map->AddKeyboardAction<PlayerJoinCommand>(InputCommands::player_join, real::KeyState::keyDown, SDL_SCANCODE_SPACE,
		GetOwner(), m_AmountOfPlayersToRegister, isPvp);

	Game::SetIsPvP(isPvp);
}

void StartScreen::PlayerSelected()
{
	--m_AmountOfPlayersToRegister;
	if (m_AmountOfPlayersToRegister == 0)
	{
		m_CurrentState = State::start;

		const auto map = real::InputManager::GetInstance().GetActiveInputMap();
		for (const auto& player : PlayerManager::GetInstance().GetPlayers())
		{
			if (player.controllerId == UCHAR_MAX)
				map->AddKeyboardAction<StartGameCommand>(InputCommands::start, real::KeyState::keyUp, SDL_SCANCODE_SPACE);
			else
				map->AddGamePadAction<StartGameCommand>(player.controllerId, InputCommands::start, real::KeyState::keyUp, real::GamePad::Button::buttonDown);
		}

		GetOwner()->GetChildAt(1)->GetComponent<FlickerText>()->Enable();
	}
}

void StartScreen::AddPlayerText(int offset, bool isEnemy, int playerId) const
{
	auto& player = GetOwner()->CreateGameObject({ glm::vec3{static_cast<float>(offset * 150),300,0} }, "player-start-screen");
	{
		player.AddComponent<real::TextureComponent>();

		real::TextInfo info{};
		info.text = "Player " + std::to_string(playerId);
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		info.horizontalAlignment = real::HorizontalTextAlignment::center;
		player.AddComponent<real::TextComponent>(std::move(info));
	}
	auto& type = player.CreateGameObject({}, "player-type");
	{
		type.GetTransform()->SetLocalPosition(0, 30);
		type.AddComponent<real::TextureComponent>();

		real::TextInfo info{};

		if (isEnemy)
		{
			info.text = "enemy";
			info.color = real::Colors::green;
		}
		else if (playerId == 1)
		{
			info.text = "pengo (red)";
			info.color = real::Colors::red;
		}
		else if (playerId == 2)
		{
			info.text = "pengo (yellow)";
			info.color = real::Colors::yellow;
		}

		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		info.horizontalAlignment = real::HorizontalTextAlignment::center;
		type.AddComponent<real::TextComponent>(std::move(info));
	}
	auto& instructions = player.CreateGameObject({}, "player-instructions");
	{
		instructions.GetTransform()->SetLocalPosition(0, 60);
		instructions.AddComponent<real::TextureComponent>();
		instructions.AddComponent<FlickerText>(real::Colors::yellow, 0.5f);

		real::TextInfo info{};
		info.text = "press space/a to join";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), 32);
		info.color = real::Colors::grey;
		info.horizontalAlignment = real::HorizontalTextAlignment::center;
		instructions.AddComponent<real::TextComponent>(std::move(info));
	}
}
