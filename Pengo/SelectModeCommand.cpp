#include "SelectModeCommand.h"

#include <GameObject.h>

#include "SelectMode.h"

SelectModeCommand::SelectModeCommand(int id, int controllerId, real::GameObject* pGameObject, bool confirm, bool goUp)
	: GameObjectCommand(id, controllerId, pGameObject)
	, m_Confirm(confirm)
	, m_GoUp(goUp)
{
}

void SelectModeCommand::Execute()
{
	if (m_Confirm)
		GetGameObject()->GetComponent<SelectMode>()->ConfirmMode();
	else
		GetGameObject()->GetComponent<SelectMode>()->Change(m_GoUp);
}
