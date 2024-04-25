#include "PlayerJoinCommand.h"

#include <GameObject.h>
#include <InputManager.h>

#include "GameInfo.h"
#include "StartScreen.h"
#include "PlayerManager.h"

PlayerJoinCommand::PlayerJoinCommand(int id, int controllerId, real::GameObject* pGameObject, int amountOfPlayers)
	: GameObjectCommand(id, controllerId, pGameObject)
{
	m_AmountOfPlayers = amountOfPlayers;
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

		PlayerManager::GetInstance().RegisterPlayer({ nullptr, {}, true, UCHAR_MAX });
		++m_CurrentPlayer;

		GetGameObject()->GetComponent<StartScreen>()->PlayerSelected();
		GetGameObject()->GetChildAt(2)->GetChildAt(1)->SetIsActive(false, true);
	}
	else
	{
		map->RemoveGamePadAction(InputCommands::player_join, GetControllerId());

		PlayerManager::GetInstance().RegisterPlayer({ nullptr, {}, false, static_cast<uint8_t>(GetControllerId()) });
		++m_CurrentPlayer;

		GetGameObject()->GetComponent<StartScreen>()->PlayerSelected();
		GetGameObject()->GetChildAt(2)->GetChildAt(1)->SetIsActive(false, true);
	}
}
