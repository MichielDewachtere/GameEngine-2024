#include "TextFadeIn.h"

#include <GameObject.h>
#include <GameTime.h>
#include <TextComponent.h>

TextFadeIn::TextFadeIn(real::GameObject* pOwner, std::string text)
	: Component(pOwner)
	, m_Text(std::move(text))
{
}

void TextFadeIn::Start()
{
	m_pTextComponent = GetOwner()->GetComponent<real::TextComponent>();
}

void TextFadeIn::Update()
{
	if (m_AccuChar == m_Text.size())
		return; // TODO: This component can be removed

	constexpr float displayTime = 0.5f;
	m_AccuTime += real::GameTime::GetInstance().GetElapsed();

	if (m_AccuTime > displayTime)
	{
		++m_AccuChar;
		m_pTextComponent->SetText(m_Text.substr(0, m_AccuChar));

		if (m_AccuChar == m_Text.size())
		{
			if (GetOwner()->GetChildCount() > 0)
				GetOwner()->GetChildAt(0)->SetIsActive(true, false);
		}
	}
}
