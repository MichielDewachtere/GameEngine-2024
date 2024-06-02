#include "PlayerJoinCommand.h"

#include <GameObject.h>
#include <InputManager.h>

#include "GameInfo.h"
#include "StartScreen.h"
#include "PlayerManager.h"

PlayerJoinCommand::PlayerJoinCommand(int id, int controllerId, real::GameObject* pGameObject, int amountOfPlayers, bool isPvp)
	: GameObjectCommand(id, controllerId, pGameObject)
	, m_IsPvP(isPvp)
{
	m_AmountOfPlayers = amountOfPlayers;
	m_CurrentPlayer = 0;
}

void PlayerJoinCommand::Execute()
{
	if (m_CurrentPlayer == m_AmountOfPlayers)
		return;

	if (std::ranges::find(m_ControllersRegistered, GetControllerId()) != m_ControllersRegistered.end())
		return;

	const auto map = real::InputManager::GetInstance().GetActiveInputMap();

	if (GetControllerId() == -1)
	{
		map->RemoveKeyboardAction(InputCommands::player_join);

		++m_CurrentPlayer;
		PlayerManager::GetInstance().SetPlayerInput(m_CurrentPlayer, true, UCHAR_MAX);

		GetGameObject()->GetComponent<StartScreen>()->PlayerSelected();
		GetGameObject()->GetChildAt(1 + m_CurrentPlayer)->GetChildAt(1)->SetIsActive(false, true);
	}
	else
	{
		map->RemoveGamePadAction(InputCommands::player_join, GetControllerId());

		++m_CurrentPlayer;
		PlayerManager::GetInstance().SetPlayerInput(m_CurrentPlayer, false, static_cast<uint8_t>(GetControllerId()));

		GetGameObject()->GetComponent<StartScreen>()->PlayerSelected();
		GetGameObject()->GetChildAt(1 + m_CurrentPlayer)->GetChildAt(1)->SetIsActive(false, true);
	}
}
