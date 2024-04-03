#include "Player.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "Move.h"

Player::Player(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

void Player::Start()
{
	m_pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();
}

void Player::Update()
{
	if (m_IsDirty && m_pSpriteComponent->IsAnimationPlaying() == false)
	{
		m_IsDirty = false;
		GetOwner()->SetIsActive(false, true);
	}
}

void Player::Die()
{
	m_pSpriteComponent->PlayAnimation(16, 17, 0);
	m_IsDirty = true;
}

void Player::ReSpawn() const
{
	GetOwner()->SetIsActive(true, true);
	m_pSpriteComponent->SelectSprite(0);
	GetOwner()->GetComponent<Move>()->Reset();
}
