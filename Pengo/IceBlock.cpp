#include "IceBlock.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "EnemyHandler.h"
#include "Game.h"
#include "Move.h"

IceBlock::IceBlock(dae::GameObject* pOwner, bool hidesEgg)
	: Component(pOwner)
	, m_HidesEgg(hidesEgg)
{
}

IceBlock::~IceBlock()
{
	GetOwner()->GetParent()->GetComponent<Game>()->gameStarted.RemoveObserver(this);
}

void IceBlock::Start()
{
	m_pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();

	GetOwner()->GetParent()->GetComponent<Game>()->gameStarted.AddObserver(this);
}

void IceBlock::Update()
{
	if (m_Break)
	{
		if (m_pSpriteComponent->IsAnimationPlaying() == false)
		{
			if (m_HidesEgg)
			{
				GetOwner()->GetParent()->GetComponent<EnemyHandler>()->RemoveEnemySpawn(GetOwner()->GetChildAt(0));
			}

			GetOwner()->Destroy();
		}

		return;
	}

	if (m_StartAnimation)
	{
		if (m_pSpriteComponent->IsAnimationPlaying() == false)
		{
			m_pSpriteComponent->SelectSprite(0);
			m_StartAnimation = false;
		}
	}
}

void IceBlock::HandleEvent(GameEvents event)
{
	if (event == GameEvents::start && m_HidesEgg)
	{
		m_pSpriteComponent->PlayAnimation(0, 1, 3, 0.5f);
		m_StartAnimation = true;
	}
}

void IceBlock::Break()
{
	if (m_Break)
		return;

	const auto maze = GetOwner()->GetParent()->GetComponent<Maze>();
	const auto move = GetOwner()->GetComponent<Move>();
	maze->SetBlock(move->GetMazePos(), Maze::BlockType::air, nullptr);
	move->Disable();

	if (m_pSpriteComponent == nullptr)
		m_pSpriteComponent = GetOwner()->GetComponent<dae::SpriteComponent>();

	m_pSpriteComponent->PlayAnimation(27, 36, 0);

	m_Break = true;
}
