#include "JoinInstructions.h"

#include <GameObject.h>
#include <TextComponent.h>
#include <GameTime.h>
#include <Colors.h>
#include <InputManager.h>

#include "EnterName.h"
#include "PlayerJoinCommand.h"
#include "GameInfo.h"
#include "HandleNameCommand.h"
#include "PlayerManager.h"

JoinInstructions::JoinInstructions(real::GameObject* pOwner)
	: Component(pOwner)
{
}

void JoinInstructions::Start()
{
	m_pTextComponent = GetOwner()->GetComponent<real::TextComponent>();
}

void JoinInstructions::Update()
{
	m_AccuTime += real::GameTime::GetInstance().GetElapsed();

	if (m_AccuTime >= m_FlickerTime)
	{
		m_pTextComponent->SetColor(m_IsYellow ? real::Colors::yellow : real::Colors::grey);

		m_IsYellow = !m_IsYellow;
		m_AccuTime = 0;
	}
}

void JoinInstructions::PlayerJoined(int controllerId)
{
	const auto map = real::InputManager::GetInstance().GetActiveInputMap();

	if (controllerId == -1)
	{
		map->RemoveKeyboardAction(InputCommands::player_join);

		const auto enterName = GetOwner()->GetParent()->GetChildAt(2);
		enterName->SetIsActive(true, true);

		map->AddKeyboardAction<HandleNameCommand>(InputCommands::name_character_confirm, real::KeyState::keyUp,
		                                          SDL_SCANCODE_SPACE, enterName, true, true);
		map->AddKeyboardAction<HandleNameCommand>(InputCommands::name_character_up, real::KeyState::keyUp,
		                                          SDL_SCANCODE_UP, enterName, false, true);
		map->AddKeyboardAction<HandleNameCommand>(InputCommands::name_character_down, real::KeyState::keyUp,
		                                          SDL_SCANCODE_DOWN, enterName, false, false);

		PlayerManager::GetInstance().RegisterPlayer({ nullptr, {}, true, UCHAR_MAX, "" });

		enterName->GetComponent<EnterName>()->LinkPlayer(static_cast<uint8_t>(m_RegisteredPlayers));
		++m_RegisteredPlayers;

		GetOwner()->SetIsActive(false, true);
	}
	else
	{
		map->RemoveGamePadAction(InputCommands::player_join, controllerId);

		const auto enterName = GetOwner()->GetParent()->GetChildAt(2);
		enterName->SetIsActive(true, true);

		map->AddGamePadAction<HandleNameCommand>(static_cast<uint8_t>(controllerId),
		                                         InputCommands::name_character_confirm, real::KeyState::keyUp,
		                                         real::GamePad::Button::buttonDown, enterName, true, true);
		map->AddGamePadAction<HandleNameCommand>(static_cast<uint8_t>(controllerId), InputCommands::name_character_up,
		                                         real::KeyState::keyUp, real::GamePad::Button::dPadUp, enterName,
		                                         false, true);
		map->AddGamePadAction<HandleNameCommand>(static_cast<uint8_t>(controllerId), InputCommands::name_character_down,
		                                         real::KeyState::keyUp, real::GamePad::Button::dPadDown, enterName,
		                                         false, false);

		PlayerManager::GetInstance().RegisterPlayer({ nullptr, {}, false, static_cast<uint8_t>(controllerId), "" });

		enterName->GetComponent<EnterName>()->LinkPlayer(static_cast<uint8_t>(m_RegisteredPlayers));
		++m_RegisteredPlayers;

		GetOwner()->SetIsActive(false, true);
	}
}