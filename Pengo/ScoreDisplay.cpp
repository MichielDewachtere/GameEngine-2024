#include "ScoreDisplay.h"

#include <GameObject.h>
#include <TextComponent.h>

ScoreDisplay::ScoreDisplay(real::GameObject* pOwner)
	: Component(pOwner)
{
}

void ScoreDisplay::Start()
{
	m_pTextComponent = GetOwner()->GetComponent<real::TextComponent>();
}

void ScoreDisplay::AddScore(ScoreEvents event)
{
	m_Score += event_to_points.at(event);
	m_pTextComponent->SetText(std::to_string(m_Score));
}

void ScoreDisplay::Reset()
{
	m_Score = 0;
	m_pTextComponent->SetText(std::to_string(m_Score));
}
