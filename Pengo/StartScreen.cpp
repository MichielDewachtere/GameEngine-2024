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

#include "JoinInstructions.h"
#include "SelectMode.h"
#include "EnterName.h"
#include "PlayerJoinCommand.h"
#include "GameInfo.h"
#include "PlayerManager.h"
#include "StartGameCommand.h"

StartScreen::StartScreen(real::GameObject* pOwner)
	: Component(pOwner)
{
}

void StartScreen::ModeSelected(Modes mode)
{
	m_CurrentState = State::selectPlayers;

	std::vector<int> playerIdcs;

	switch (mode)
	{
		case Modes::singlePlayer:
		{
			m_AmountOfPlayersToRegister = 1;
			playerIdcs.push_back(AddPlayerText(0, false, 1));
			break;
		}
		case Modes::coOp:
		{
			m_AmountOfPlayersToRegister = 2;
			playerIdcs.push_back(AddPlayerText(-1, false, 1));
			playerIdcs.push_back(AddPlayerText(1, false, 2));
			break;
		}
		case Modes::pvp:
		{
			m_AmountOfPlayersToRegister = 2;
			playerIdcs.push_back(AddPlayerText(-1, false, 1));
			playerIdcs.push_back(AddPlayerText(1, true, 2));
			break;
		}
	}

	auto& input = real::InputManager::GetInstance();
	const auto map = input.GetActiveInputMap();

	for (const auto& gamePads : input.GetGamePads())
	{
		map->AddGamePadAction<PlayerJoinCommand>(gamePads->GetIndex(), InputCommands::player_join, real::KeyState::keyDown,
			real::GamePad::Button::buttonDown, GetOwner(), playerIdcs);
	}

	map->AddKeyboardAction<PlayerJoinCommand>(InputCommands::player_join, real::KeyState::keyDown, SDL_SCANCODE_SPACE,
		GetOwner(), playerIdcs);
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
	}
}

void StartScreen::Update()
{
	if (m_CurrentState == State::start)
	{
		m_AccuTime += real::GameTime::GetInstance().GetElapsed();

		if (m_AccuTime > m_FlickerTime)
		{
			m_AccuTime = 0;
			m_IsYellow = !m_IsYellow;
			GetOwner()->GetChildAt(1)->GetComponent<real::TextComponent>()->SetColor(m_IsYellow ? real::Colors::yellow : real::Colors::grey);
		}
	}
}

int StartScreen::AddPlayerText(int offset, bool isEnemy, int playerId) const
{
	auto& player = GetOwner()->CreateGameObject("player-start-screen");
	{
		auto pFont = real::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

		player.GetTransform()->SetLocalPosition(static_cast<float>(offset * 150), 300);
		player.AddComponent<real::TextureComponent>();

		const auto text = "Player " + std::to_string(playerId);
		const auto textComponent = player.AddComponent<real::TextComponent>(text, std::move(pFont));
		textComponent->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		textComponent->SetColor(real::Colors::grey);
	}
	auto& type = player.CreateGameObject("player-type");
	{
		auto pFont = real::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 20);

		type.GetTransform()->SetLocalPosition(0, 30);
		type.AddComponent<real::TextureComponent>();

		std::string text{};
		glm::u8vec4 color{};
		if (isEnemy)
		{
			text = "enemy";
			color = real::Colors::green;
		}
		else if (playerId == 1)
		{
			text = "pengo (red)";
			color = real::Colors::red;
		}
		else if (playerId == 2)
		{
			text = "pengo (yellow)";
			color = real::Colors::yellow;
		}

		const auto textComponent = type.AddComponent<real::TextComponent>(text, std::move(pFont));
		textComponent->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		textComponent->SetColor(color);
	}
	auto& instructions = player.CreateGameObject("player-instructions");
	{
		auto pFont = real::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 16);

		instructions.GetTransform()->SetLocalPosition(0, 60);
		instructions.AddComponent<real::TextureComponent>();
		instructions.AddComponent<JoinInstructions>();

		const auto textComponent = instructions.AddComponent<real::TextComponent>("press space/a to join", std::move(pFont));
		textComponent->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		textComponent->SetColor(real::Colors::grey);
	}
	auto& enterName = player.CreateGameObject();
	enterName.SetIsActive(false, true);
	{
		auto pFont = real::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);
		enterName.GetTransform()->SetLocalPosition(0, 60);
		enterName.AddComponent<EnterName>();
		enterName.AddComponent<real::TextureComponent>();

		const auto textComponent = enterName.AddComponent<real::TextComponent>("name", std::move(pFont));
		textComponent->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);
		textComponent->SetColor(real::Colors::grey);
	}

	return player.GetId();
}
