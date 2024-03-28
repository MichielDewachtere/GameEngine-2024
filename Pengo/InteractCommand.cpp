#include "InteractCommand.h"

#include <GameObject.h>

#include "Interact.h"

InteractCommand::InteractCommand(int id, int controllerId, dae::GameObject* pGameObject)
	: GameObjectCommand(id, controllerId, pGameObject)
{
	m_pInteractComponent = GetGameObject()->GetComponent<Interact>();
}

void InteractCommand::Execute()
{
	m_pInteractComponent->AttemptInteraction();
}
