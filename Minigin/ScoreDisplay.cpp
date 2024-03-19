#include "stdafx.h"
#include "ScoreDisplay.h"

#include "GameObject.h"
#include "Player.h"
#include "TextComponent.h"

ScoreDisplay::ScoreDisplay(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

ScoreDisplay::~ScoreDisplay()
{
	m_pLinkedPlayer->scoreChanged.RemoveObserver(this);
}

void ScoreDisplay::HandleEvent(uint32_t score)
{
	if (m_pTextComponent == nullptr)
		m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();

	std::string text = "Score: ";
	text += std::to_string(score);
	m_pTextComponent->SetText(text);
}

void ScoreDisplay::OnSubjectDestroy()
{
	m_pLinkedPlayer->scoreChanged.RemoveObserver(this);
}

void ScoreDisplay::SetLinkedPlayer(Player* pPlayer)
{
	m_pLinkedPlayer = pPlayer;
	m_pLinkedPlayer->scoreChanged.AddObserver(this);
}
