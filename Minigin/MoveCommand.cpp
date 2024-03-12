#include "stdafx.h"
#include "MoveCommand.h"

#include "GameObject.h"
#include "GameTime.h"

MoveCommand::MoveCommand(dae::GameObject* pGameObject, const glm::ivec2& direction, int speed)
	: GameObjectCommand(pGameObject)
	, m_Speed(speed)
	, m_Direction(direction)
{
	if (m_Direction.x < -1 || m_Direction.x > 1)
		m_Direction.x = 0;
	if (m_Direction.y < -1 || m_Direction.y > 1)
		m_Direction.y = 0;
}

void MoveCommand::Execute()
{
	const auto dt = dae::GameTime::GetInstance().GetElapsed();
	GetGameObject()->GetTransform()->Translate({ m_Speed * m_Direction.x * dt, m_Speed * m_Direction.y * dt });
}
