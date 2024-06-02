#include "IceBlock.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "EnemyHandler.h"
#include "Game.h"
#include "GameInfo.h"
#include "GameUtil.h"
#include "HiddenEgg.h"
#include "HUD.h"
#include "Locator.h"
#include "Move.h"
#include "ScoreDisplay.h"

IceBlock::IceBlock(real::GameObject* pOwner, bool hidesEgg, ECharacterColors color)
	: Component(pOwner)
	, m_Color(color)
	, m_HidesEgg(hidesEgg)
{
}

IceBlock::~IceBlock()
{
	if (const auto game = GetOwner()->GetParent()->GetComponent<Game>();
		game != nullptr)
		game->gameEvent.RemoveObserver(this);
}

void IceBlock::Start()
{
	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();

	GetOwner()->GetParent()->GetComponent<Game>()->gameEvent.AddObserver(this);
}

void IceBlock::Update()
{
	if (m_Break)
	{
		if (m_pSpriteComponent->IsAnimationPlaying() == false)
		{
			if (m_HidesEgg)
			{
				GetOwner()->GetChildAt(0)->GetComponent<HiddenEgg>()->BreakEgg();
				HUD::GetInstance().AddScore(ScoreEvents::breakEgg, m_BreakedBy);
			}
			else
			{
				HUD::GetInstance().AddScore(ScoreEvents::breakIce, m_BreakedBy);
				GetOwner()->Destroy();
			}

			m_Break = false;
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
	if ((event == GameEvents::started || event == GameEvents::resumed) && m_HidesEgg)
	{

		m_pSpriteComponent->PlayAnimation({ 0,GetSpriteIndexFromColor(m_Color) }, 3, 0.5f);
		//m_pSpriteComponent->PlayAnimation(0, 1, 3, 0.5f);
		m_StartAnimation = true;
	}
}

void IceBlock::Break(PlayerNumber breakedBy)
{
	if (m_Break)
		return;

	real::Locator::GetAudioSystem().Play(Sounds::ice_destroyed);

	const auto maze = GetOwner()->GetParent()->GetComponent<Maze>();
	const auto move = GetOwner()->GetComponent<Move>();
	//maze->SetBlock(move->GetMazePos(), Maze::BlockType::air, nullptr);
	maze->RemoveBlock(move->GetMazePos(), GetOwner());
	move->Disable();

	if (m_pSpriteComponent == nullptr)
		m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();

	m_pSpriteComponent->PlayAnimation(27, 36, 0);

	m_BreakedBy = breakedBy;

	m_Break = true;
}
