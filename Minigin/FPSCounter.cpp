#include "stdafx.h"
#include "FPSCounter.h"

#include "GameObject.h"
#include "GameTime.h"
#include "TextComponent.h"

FPSCounter::FPSCounter(dae::GameObject* pOwner)
	: Component(pOwner)
{
	// TODO: implement this
	if (m_pTextComponent == nullptr)
		m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

//FPSCounter::~FPSCounter()
//{
//	if (m_pTextComponent == nullptr)
//	{
//		delete m_pTextComponent;
//		m_pTextComponent = nullptr;
//	}
//}

void FPSCounter::Start()
{
	//if (m_pTextComponent == nullptr)
	//	m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

void FPSCounter::Update()
{
	const auto fps = dae::GameTime::GetInstance().GetFPS();
	//if (const auto pText = GetOwner()->GetComponent<dae::TextComponent>();
	//	pText != nullptr)
	//{
	//	if (m_PreviousFPS != fps)
	//	{
	//		// Expensive operation (New texture is being made), do this only if strings are different
	//		pText->SetText(std::to_string(fps));
	//		m_PreviousFPS = fps;
	//	}
	//}
	if (m_pTextComponent != nullptr)
	{
		if (m_PreviousFPS != fps)
		{
			// Expensive operation (New texture is being made), do this only if strings are different
			m_pTextComponent->SetText(std::to_string(fps));
			m_PreviousFPS = fps;
		}
	}
	else
	{
		m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
		///*m_pTextComponent = */GetOwner()->AddComponent<dae::TextComponent>(std::to_string(fps), "Lingua.otf");
	}
}