#include "Wall.h"

#include <GameObject.h>
#include <SpriteComponent.h>

#include "Maze.h"

Wall::Wall(real::GameObject* pOwner, WallOrientation orientation)
	: Component(pOwner)
	, m_Orientation(orientation)
{
}

void Wall::Start()
{
	m_pMazeComponent = GetOwner()->GetParent()->GetComponent<Maze>();
	m_pSpriteComponent = GetOwner()->GetComponent<real::SpriteComponent>();
}

void Wall::Update()
{
	if (m_IsDirty)
	{
		if (m_pSpriteComponent->IsAnimationPlaying() == false)
		{
			m_pSpriteComponent->SelectSprite(0);
			m_IsDirty = false;
		}
	}
}

void Wall::Shake()
{
	m_IsDirty = true;
	wallShaked.Notify(m_Orientation);
	m_pSpriteComponent->PlayAnimation(1, 2, 2);
}