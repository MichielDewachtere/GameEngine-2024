#include "FlickerText.h"

#include <GameObject.h>
#include <TextComponent.h>
#include <GameTime.h>
#include <InputManager.h>

FlickerText::FlickerText(real::GameObject* pOwner, glm::u8vec4 flickerColor, float flickerTime)
	: Component(pOwner)
	, m_FlickerTime(flickerTime)
	, m_FlickerColor(std::move(flickerColor))
{
}

void FlickerText::Start()
{
	m_pTextComponent = GetOwner()->GetComponent<real::TextComponent>();
	m_OriginalColor = m_pTextComponent->GetColor();
}

void FlickerText::Update()
{
	m_AccuTime += real::GameTime::GetInstance().GetElapsed();

	if (m_AccuTime >= m_FlickerTime)
	{
		m_pTextComponent->SetColor(m_IsOriginal ? m_OriginalColor : m_FlickerColor);

		m_IsOriginal = !m_IsOriginal;
		m_AccuTime = 0;
	}
}