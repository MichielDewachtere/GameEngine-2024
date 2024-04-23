#include "PlayerJoinCommand.h"

#include <GameObject.h>

#include "JoinInstructions.h"

PlayerJoinCommand::PlayerJoinCommand(int id, int controllerId, real::GameObject* pGameObject,
                                     std::vector<int> playerIdcs)
	: GameObjectCommand(id, controllerId, pGameObject)
	, m_PlayerIdcs(std::move(playerIdcs))
{
}

void PlayerJoinCommand::Execute()
{
	if (m_CurrentPlayer == static_cast<int>(m_PlayerIdcs.size()))
		return;

	if (std::ranges::find(m_ControllersRegistered, GetControllerId()) != m_ControllersRegistered.end())
		return;

	m_ControllersRegistered.push_back(GetControllerId());
	GetGameObject()->GetChild(m_PlayerIdcs[m_CurrentPlayer])->GetChildAt(1)->GetComponent<JoinInstructions>()->PlayerJoined(GetControllerId());
	++m_CurrentPlayer;
}
