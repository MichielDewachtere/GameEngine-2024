#include "HiddenEgg.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "Enemy.h"
#include "EnemyHandler.h"
#include "IceBlock.h"

HiddenEgg::HiddenEgg(real::GameObject* pOwner)
	: Component(pOwner)
{
}

HiddenEgg::~HiddenEgg() = default;

void HiddenEgg::Start()
{
	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();
}

void HiddenEgg::Update()
{
	if (m_EggPopped)
	{
		switch (m_CurrentState)
		{
		case EggBreakSequence::iceBreakAnim:
		{
			if (m_IceBlockSpriteComponent->IsAnimationPlaying() == false)
			{
				m_pSpriteComponent->Enable();
				m_pSpriteComponent->PlayAnimation(0, 2, 3);
				m_CurrentState = EggBreakSequence::eggFlashAnim;
				GetOwner()->GetParent()->GetParent()->GetComponent<EnemyHandler>()->RemoveEnemySpawn(GetOwner());
			}
			break;
		}
		case EggBreakSequence::eggFlashAnim:
		{
			if (m_pSpriteComponent->IsAnimationPlaying() == false)
			{
				m_pSpriteComponent->PlayAnimation(1, 5, 0, 0.25f);
				m_CurrentState = EggBreakSequence::eggBreakAnim;
			}
			break;
		}
		case EggBreakSequence::eggBreakAnim:
		{
			if (m_pSpriteComponent->IsAnimationPlaying() == false)
			{
				m_CurrentState = EggBreakSequence::destroyEgg;
			}
			break;
		}
		case EggBreakSequence::destroyEgg:
		{
			GetOwner()->GetParent()->Destroy();
			break;
		}
		}
	}
}

void HiddenEgg::PopEgg()
{
	m_EggPopped = true;

	GetOwner()->GetParent()->GetComponent<IceBlock>()->Break();

	//if (m_pSpriteComponent == nullptr)
	//	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();

	{
		//m_pSpriteComponent->Enable();
		//m_pSpriteComponent->PlayAnimation(0, 2, 3);
		m_CurrentState = EggBreakSequence::destroyEgg;
	}
	//else
	//{
	//	m_IceBlockSpriteComponent = GetOwner()->GetParent()->GetComponent<real::SpriteComponent>();
	//}
}

void HiddenEgg::BreakEgg()
{
	m_EggPopped = true;

	GetOwner()->GetParent()->GetComponent<IceBlock>()->Break();

	if (m_pSpriteComponent == nullptr)
		m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();

	m_CurrentState = EggBreakSequence::iceBreakAnim;
	m_IceBlockSpriteComponent = GetOwner()->GetParent()->GetComponent<real::SpriteComponent>();
}
