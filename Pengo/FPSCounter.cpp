#include "FPSCounter.h"

#include <GameObject.h>
#include <GameTime.h>
#include <ResourceManager.h>
#include <TextComponent.h>

FPSCounter::FPSCounter(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

void FPSCounter::Start()
{
	if (m_pTextComponent == nullptr)
		m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
}

void FPSCounter::Update()
{
	const auto fps = dae::GameTime::GetInstance().GetFPS_Unsigned();
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
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
		m_pTextComponent = GetOwner()->AddComponent<dae::TextComponent>(std::to_string(fps), std::move(font));
	}
}