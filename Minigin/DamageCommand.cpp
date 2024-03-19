#include "stdafx.h"
#include "DamageCommand.h"

#include "GameObject.h"

DamageCommand::DamageCommand(int id, int controllerId, dae::GameObject* pOwner)
	: GameObjectCommand(id, controllerId, pOwner)
{
	m_pPlayer = GetGameObject()->GetComponent<Player>();
}

void DamageCommand::Execute()
{
	m_pPlayer->Damage();
}
