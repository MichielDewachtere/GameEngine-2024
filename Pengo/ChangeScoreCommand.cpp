#include "ChangeScoreCommand.h"

#include <GameObject.h>

ChangeScoreCommand::ChangeScoreCommand(int id, int controllerId, dae::GameObject* pOwner, int scoreChange)
	: GameObjectCommand(id, controllerId, pOwner)
	, m_ScoreChange(scoreChange)
{
	m_pPlayer = GetGameObject()->GetComponent<Player>();
}

void ChangeScoreCommand::Execute()
{
	m_pPlayer->AddScore(m_ScoreChange);
}
