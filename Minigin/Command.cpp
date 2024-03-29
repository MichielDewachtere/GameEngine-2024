#include "Command.h"

#include <iostream>

#include "GameObject.h"
#include "InputManager.h"

dae::GameObjectCommand::GameObjectCommand(int id, int controllerId, GameObject* pGameObject)
	: Command(id, controllerId), m_pGameObject(pGameObject)
{
	GetGameObject()->gameObjectDestroyed.AddObserver(this);
}

dae::GameObjectCommand::~GameObjectCommand()
{
	if (GetGameObject()->IsMarkedForDestroy() == false && m_ObserverRemoved == false)
	{
		m_ObserverRemoved = true;
		GetGameObject()->gameObjectDestroyed.RemoveObserver(this);
	}
}

void dae::GameObjectCommand::HandleEvent(GameObjectEvent)
{
	if (GetControllerId() == -1)
		InputManager::GetInstance().GetActiveInputMap()->RemoveKeyboardAction(static_cast<uint8_t>(GetId()));
	else
		InputManager::GetInstance().GetActiveInputMap()->RemoveGamePadAction(static_cast<uint8_t>(GetId()), static_cast<uint8_t>(GetControllerId()));
}

void dae::GameObjectCommand::OnSubjectDestroy()
{
	if (m_ObserverRemoved == false)
	{
		m_ObserverRemoved = true;
		GetGameObject()->gameObjectDestroyed.RemoveObserver(this);
	}
}

void dae::TestCommand::Execute()
{
	std::cout << "Test command succeeded\n";
}
