#include "DiedState.h"

#include <GameObject.h>

#include "Enemy.h"
#include "Game.h"
#include "GameInfo.h"
#include "Locator.h"
#include "Move.h"
#include "Maze.h"

DiedState::DiedState(real::GameObject* pOwner)
	: IEnemyState(pOwner)
{
}

void DiedState::Enter()
{
	real::Locator::GetAudioSystem().Play(Sounds::sno_bee_killed);

	if (const auto enemyComp = GetOwner()->GetComponent<Enemy>())
		enemyComp->enemyDied.Notify();
	else
		GetOwner()->GetParent()->GetComponent<Game>()->EndAct(true);

	const auto pos = GetOwner()->GetComponent<Move>()->GetMazePos();
	GetOwner()->GetParent()->GetComponent<Maze>()->RemoveBlock(pos, GetOwner());
	 
	GetOwner()->Destroy();
}
