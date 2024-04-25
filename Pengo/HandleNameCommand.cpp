#include "HandleNameCommand.h"

#include <GameObject.h>
#include <Locator.h>

#include "EnterName.h"
#include "GameInfo.h"

HandleNameCommand::HandleNameCommand(int id, int controllerId, real::GameObject* pGameObject, bool enter, bool up)
	: GameObjectCommand(id, controllerId, pGameObject)
	, m_Enter(enter)
	, m_Up(up)
{
	m_pEnterNameComponent = GetGameObject()->GetComponent<EnterName>();
}

void HandleNameCommand::Start()
{
}

void HandleNameCommand::Execute()
{
	if (m_Enter)
	{
		m_pEnterNameComponent->EnterCharacter(GetControllerId());
	}
	else
		m_pEnterNameComponent->ChangeCharacter(m_Up);

	real::Locator::GetAudioSystem().Play(Sounds::test);
}
