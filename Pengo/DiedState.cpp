#include "DiedState.h"

#include <GameObject.h>

#include "Enemy.h"
#include "Move.h"
#include "Maze.h"

DiedState::DiedState(real::GameObject* pOwner)
	: IEnemyState(pOwner)
{
}

IEnemyState* DiedState::Update()
{
	GetOwner()->GetComponent<Enemy>()->enemyDied.Notify();

	const auto pos = GetOwner()->GetComponent<Move>()->GetMazePos();
	GetOwner()->GetParent()->GetComponent<Maze>()->RemoveBlock(pos, GetOwner());
	 
	GetOwner()->Destroy();
	return nullptr;
}
