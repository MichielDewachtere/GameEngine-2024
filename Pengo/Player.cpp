#include "Player.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "Move.h"

Player::Player(real::GameObject* pOwner, PlayerNumber number, bool isEnemy)
	: Component(pOwner)
	, m_PlayerNumber(number)
	, m_IsEnemy(isEnemy)
{
}

void Player::Start()
{
	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();
}

void Player::Update()
{
	if (m_IsDying && m_pSpriteComponent->IsAnimationPlaying() == false)
	{
		m_IsDying = false;
		GetOwner()->SetIsActive(false, true);
	}
}

void Player::Die()
{
	m_pSpriteComponent->PlayAnimation(16, 17, 0);
	m_IsDying = true;
}

void Player::ReSpawn() const
{
	GetOwner()->SetIsActive(true, true);
	m_pSpriteComponent->SelectSprite(m_ReSpawnSprite);
	GetOwner()->GetComponent<Move>()->Reset();
}

bool Player::IsEnemy() const
{
	return m_IsEnemy;
}
