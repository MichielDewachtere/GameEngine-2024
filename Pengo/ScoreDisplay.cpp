#include "ScoreDisplay.h"

#include <GameObject.h>
#include <TextComponent.h>

ScoreDisplay::ScoreDisplay(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

void ScoreDisplay::Start()
{
	m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

void ScoreDisplay::AddScore(ScoreEvents event)
{
	m_Score += event_to_points.at(event);
	m_pTextComponent->SetText(std::to_string(m_Score));
}
