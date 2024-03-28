#include "Enemy.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "Game.h"
#include "Macros.h"
#include "Maze.h"
#include "Move.h"
#include "Pushable.h"

std::map<Direction, std::pair<int, int>> Enemy::m_DirectionToSquashAnim
{
	{Direction::up, {32,33}},
	{Direction::right, {34,35}},
	{Direction::down, {36,37}},
	{Direction::left, {38,39}}
};


Enemy::Enemy(dae::GameObject* pOwner)
	: Component(pOwner)
{
}

Enemy::~Enemy() = default;

void Enemy::Start()
{
	m_pMoveComponent = GetOwner()->GetComponent<Move>();
	m_pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();
	m_PushableComponent = GetOwner()->GetComponent<Pushable>();

	m_pMoveComponent->Animate(false);
	m_pSpriteComponent->PlayAnimation(0, 5, 0);
}

void Enemy::Update()
{
	switch (m_CurrentState)
	{
	case EnemyState::spawned:
	{
		if (m_pSpriteComponent->IsAnimationPlaying() == false)
		{
			m_pSpriteComponent->PlayAnimation(8, 9);
			m_CurrentState = EnemyState::moving;
		}
		break;
	}
	case EnemyState::moving:
	{

		break;
	}
	case EnemyState::pushed:
	{
		if (m_PushableComponent->IsBeingPushed())
		{
			m_pSpriteComponent->Pause(true);
		}
		else
		{
			if (m_pSpriteComponent->IsPaused())
			{
				m_pSpriteComponent->Pause(false);
				m_pSpriteComponent->PlayAnimation(m_DirectionToSquashAnim[m_PushDirection].first,
				                                  m_DirectionToSquashAnim[m_PushDirection].second, 
				                                  0, 0.1f);
			}
			else if (m_pSpriteComponent->IsAnimationPlaying() == false)
			{
				m_CurrentState = EnemyState::died;
				m_pSpriteComponent->Disable();
			}
		}
		break;
	}
	case EnemyState::stunned:
	{

		break;
	}
	case EnemyState::died:
	{
		enemyDied.Notify();

		//auto pos = m_pMoveComponent->GetMazePos();
		//GetOwner()->GetParent()->GetComponent<Maze>()->SetBlock(pos, Maze::BlockType::air);

		GetOwner()->Destroy();
		break;
	}
	}
}

void Enemy::HandleEvent(dae::GameObjectEvent event)
{
	if (event == dae::GameObjectEvent::destroyed)
		enemyDied.Destroy();
}

void Enemy::Push(Direction direction)
{
	m_CurrentState = EnemyState::pushed;
	m_PushDirection = direction;
	GetOwner()->GetComponent<Pushable>()->Push(direction);
	m_pMoveComponent->SetMovementSpeed(PUSH_SPEED);
}
