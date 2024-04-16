#include "MoveCommand.h"

#include <GameObject.h>

#include "Move.h"

MoveCommand::MoveCommand(int id, int controllerId, real::GameObject* pGameObject, Direction direction)
	: GameObjectCommand(id, controllerId, pGameObject)
	, m_Direction(direction)
{
	m_pMoveComponent = GetGameObject()->GetComponent<Move>();
}

void MoveCommand::Execute()
{
	m_pMoveComponent->MoveInDirection(m_Direction);
}
