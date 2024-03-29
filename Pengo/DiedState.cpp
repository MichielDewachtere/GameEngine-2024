#include "DiedState.h"

#include <GameObject.h>

#include "Enemy.h"

DiedState::DiedState(dae::GameObject* pOwner)
	: IEnemyState(pOwner)
{
}

IEnemyState* DiedState::Update()
{
	GetOwner()->GetComponent<Enemy>()->enemyDied.Notify();
	GetOwner()->Destroy();
	return nullptr;
}
