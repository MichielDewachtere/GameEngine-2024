#include "stdafx.h"
#include "LivesDisplay.h"

#include "GameObject.h"
#include "Player.h"
#include "TextComponent.h"

LivesDisplay::LivesDisplay(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

LivesDisplay::~LivesDisplay()
{
	m_pLinkedPlayer->healthChanged.RemoveObserver(this);
}

void LivesDisplay::
HandleEvent(unsigned char lifes)
{
	if (m_pTextComponent == nullptr)
		m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();

	std::string text = "Amount of lifes left: ";
	text += std::to_string(lifes);
	m_pTextComponent->SetText(text);
}

void LivesDisplay::OnSubjectDestroy()
{
	m_pLinkedPlayer->healthChanged.RemoveObserver(this);
}

void LivesDisplay::SetLinkedPlayer(Player* pPlayer)
{
	m_pLinkedPlayer = pPlayer;
	m_pLinkedPlayer->healthChanged.AddObserver(this);
}
