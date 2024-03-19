#include "MoveCommand.h"

#include <GameObject.h>
#include <GameTime.h>

MoveCommand::MoveCommand(int id, int controllerId, dae::GameObject* pGameObject, const glm::ivec2& direction, int speed)
	: GameObjectCommand(id, controllerId, pGameObject)
	, m_Speed(speed)
	, m_Direction(direction)
{
	if (m_Direction.x < -1 || m_Direction.x > 1)
		m_Direction.x = 0;
	if (m_Direction.y < -1 || m_Direction.y > 1)
		m_Direction.y = 0;

	//glm::normalize(m_Direction);
}

void MoveCommand::Execute()
{
	if (GetGameObject()->GetTransform() == nullptr)
		return;

	const auto dt = dae::GameTime::GetInstance().GetElapsed();
	GetGameObject()->GetTransform()->Translate({ m_Speed * m_Direction.x * dt, m_Speed * m_Direction.y * dt });
}