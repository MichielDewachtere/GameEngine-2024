#include "HiddenEgg.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "Enemy.h"
#include "IceBlock.h"

HiddenEgg::HiddenEgg(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

HiddenEgg::~HiddenEgg() = default;

void HiddenEgg::Start()
{
	m_pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();
}

void HiddenEgg::Update()
{
	if (m_EggPopped && m_pSpriteComponent->IsAnimationPlaying() == false)
	{
		GetOwner()->GetParent()->Destroy();
	}
}

void HiddenEgg::PopEgg()
{
	m_EggPopped = true;

	GetOwner()->GetParent()->GetComponent<IceBlock>()->Break();

	if (m_pSpriteComponent == nullptr)
		m_pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();

	m_pSpriteComponent->Enable();
	m_pSpriteComponent->PlayAnimation(0, 2, 3);
}