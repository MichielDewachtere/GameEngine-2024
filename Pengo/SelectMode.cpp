﻿#include "SelectMode.h"

#include <GameObject.h>
#include <TextComponent.h>
#include <TextureComponent.h>
#include <ResourceManager.h>
#include <Colors.h>
#include <InputManager.h>

#include "GameInfo.h"
#include "Macros.h"
#include "PlayerManager.h"
#include "SelectModeCommand.h"
#include "StartScreen.h"

SelectMode::SelectMode(real::GameObject* pOwner)
	: Component(pOwner)
{
}

void SelectMode::Start()
{
	for (char i = 0; i < static_cast<char>(Modes::amountOfModes); ++i)
	{
		InitMode(i);
	}

	const auto& input = real::InputManager::GetInstance();
	const auto map = input.GetActiveInputMap();

	if (map == nullptr)
		return;

	for (const auto& gamePads : input.GetGamePads())
	{
		map->AddGamePadAction<SelectModeCommand>(gamePads->GetIndex(), InputCommands::mode_confirm, real::KeyState::keyUp,
		                                         real::GamePad::Button::buttonDown, GetOwner(), true, false);
		map->AddGamePadAction<SelectModeCommand>(gamePads->GetIndex(), InputCommands::mode_go_up, real::KeyState::keyUp,
		                                         real::GamePad::Button::dPadUp, GetOwner(), false, true);
		map->AddGamePadAction<SelectModeCommand>(gamePads->GetIndex(), InputCommands::mode_go_down, real::KeyState::keyUp,
		                                         real::GamePad::Button::dPadDown, GetOwner(), false, false);
	}

	map->AddKeyboardAction<SelectModeCommand>(InputCommands::mode_confirm, real::KeyState::keyUp, SDL_SCANCODE_SPACE,
	                                          GetOwner(), true, false);
	map->AddKeyboardAction<SelectModeCommand>(InputCommands::mode_go_up, real::KeyState::keyUp, SDL_SCANCODE_UP,
	                                          GetOwner(), false, true);
	map->AddKeyboardAction<SelectModeCommand>(InputCommands::mode_go_down, real::KeyState::keyUp, SDL_SCANCODE_DOWN,
	                                          GetOwner(), false, false);
}

void SelectMode::Change(bool goUp)
{
	m_TextComponents[m_CurrentMode]->SetColor(real::Colors::grey);

	if (goUp)
		m_CurrentMode = static_cast<Modes>((static_cast<char>(m_CurrentMode) - 1 + 3) % 3);
	else
		m_CurrentMode = static_cast<Modes>((static_cast<int>(m_CurrentMode) + 1) % 3);

	m_TextComponents[m_CurrentMode]->SetColor(real::Colors::yellow);
}

void SelectMode::ConfirmMode() const
{
	// ReSharper disable once CppIncompleteSwitchStatement
	// ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
	switch (m_CurrentMode)
	{
	case Modes::singlePlayer:
		PlayerManager::GetInstance().SetAmountOfPlayers(1, false);
		break;
	case Modes::coOp:
		PlayerManager::GetInstance().SetAmountOfPlayers(2, false);
		break;
	case Modes::pvp:
		PlayerManager::GetInstance().SetAmountOfPlayers(2, true);
		break;
	}

	const auto startScreen = GetOwner()->GetParent()->GetComponent<StartScreen>();
	startScreen->ModeSelected(m_CurrentMode);

	const auto map = real::InputManager::GetInstance().GetActiveInputMap();
	map->RemoveKeyboardAction(InputCommands::mode_go_down);
	map->RemoveKeyboardAction(InputCommands::mode_go_up);
	map->RemoveKeyboardAction(InputCommands::mode_confirm);

	map->RemoveGamePadAction(InputCommands::mode_go_down, -1);
	map->RemoveGamePadAction(InputCommands::mode_go_up, -1);
	map->RemoveGamePadAction(InputCommands::mode_confirm, -1);
}

void SelectMode::InitMode(char id)
{
	auto& mode = GetOwner()->CreateGameObject();
	mode.GetTransform()->SetLocalPosition(0, static_cast<float>(40 + id * 30));
	mode.AddComponent<real::TextureComponent>();

	real::TextInfo info{};

	if (static_cast<Modes>(id) == Modes::singlePlayer)
		info.color = real::Colors::yellow;
	else
		info.color = real::Colors::grey;

	info.text = m_ModeNames[static_cast<Modes>(id)];
	info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), 40);
	info.horizontalAlignment = real::HorizontalTextAlignment::center;
	m_TextComponents[static_cast<Modes>(id)] = mode.AddComponent<real::TextComponent>(std::move(info));
}
