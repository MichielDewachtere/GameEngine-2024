#include "EnemyPlayer.h"

#include <GameObject.h>

#include "MoveState.h"
#include "Move.h"
#include "StunState.h"

EnemyPlayer::EnemyPlayer(real::GameObject* pOwner, PlayerNumber number)
	: Player(pOwner, number, true)
{
	m_pCurrentState = std::make_unique<MoveState>(GetOwner(), true);
	m_pCurrentState->Enter();

	m_ReSpawnSprite = 8;
}

EnemyPlayer::~EnemyPlayer()
{
	if (const auto game = GetOwner()->GetParent()->GetComponent<Game>())
		game->gameEvent.RemoveObserver(this);

	Enemy::WallObservers(this, GetOwner()->GetParent()->GetComponent<Maze>(), true);
}

void EnemyPlayer::Start()
{
	if (const auto game = GetOwner()->GetParent()->GetComponent<Game>())
		game->gameEvent.AddObserver(this);

	Enemy::WallObservers(this, GetOwner()->GetParent()->GetComponent<Maze>(), false);

	Player::Start();
}

void EnemyPlayer::Update()
{
	if (const auto newState = m_pCurrentState->Update())
	{
		m_pCurrentState->Exit();
		newState->Enter();
		m_pCurrentState.reset(newState);
	}
}

void EnemyPlayer::HandleEvent(GameEvents event)
{
	switch (event)
	{
	case GameEvents::finished:
	case GameEvents::paused:
	{
		m_pCurrentState->Exit();
		Disable();
		break;
	}
	case GameEvents::resumed:
	{
		m_pCurrentState.reset(new MoveState(GetOwner(), true));
		m_pCurrentState->Enter();
		Enable();
		break;
	}
	}
}

void EnemyPlayer::HandleEvent(WallOrientation orientation)
{
	if (dynamic_cast<StunState*>(m_pCurrentState.get()) != nullptr)
		return;

	const auto mazePos = GetOwner()->GetComponent<Move>()->GetMazePos();
	
	if (Enemy::m_OrientationToPos[orientation].x == mazePos.x
		|| Enemy::m_OrientationToPos[orientation].y == mazePos.y)
	{
		m_pCurrentState->Exit();
		m_pCurrentState.reset(new StunState(GetOwner(), true));
		m_pCurrentState->Enter();
	}
}

void EnemyPlayer::Push(Direction direction)
{
	Enemy::PushHelper(m_pCurrentState, *GetOwner()->GetComponent<Move>(), direction);
}
