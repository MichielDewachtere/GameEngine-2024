#include "SelectMode.h"

#include <GameObject.h>
#include <TextComponent.h>
#include <TextureComponent.h>
#include <ResourceManager.h>
#include <Colors.h>
#include <InputManager.h>

#include "GameInfo.h"
#include "Macros.h"
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
	auto pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);

	auto& mode = GetOwner()->CreateGameObject();
	mode.GetTransform()->SetLocalPosition(0, static_cast<float>(50 + id * 25));
	mode.AddComponent<real::TextureComponent>();

	const auto textComponent = mode.AddComponent<real::TextComponent>(m_ModeNames[static_cast<Modes>(id)], std::move(pFont));
	textComponent->SetHorizontalAlignment(real::TextComponent::HorizontalAlignment::center);

	if (static_cast<Modes>(id) == Modes::singlePlayer)
		textComponent->SetColor(real::Colors::yellow);
	else
		textComponent->SetColor(real::Colors::grey);

	m_TextComponents[static_cast<Modes>(id)] = textComponent;
}
