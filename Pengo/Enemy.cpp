#include "Enemy.h"

#include <GameObject.h>

#include "Macros.h"

#include "Game.h"
#include "Maze.h"
#include "Wall.h"
#include "Move.h"

#include "DiedState.h"
#include "MoveState.h"
#include "PushedState.h"
#include "SpawnState.h"
#include "StunState.h"

std::map<WallOrientation, glm::ivec2> Enemy::m_OrientationToPos{
	{WallOrientation::north, {-1, 0}},
	{WallOrientation::east, {MAZE_WIDTH - 1, -1}},
	{WallOrientation::south, {-1, MAZE_HEIGHT - 1}},
	{WallOrientation::west, {0,-1}},
};

Enemy::Enemy(real::GameObject* pOwner)
	: Component(pOwner)
{
}

Enemy::~Enemy()
{
	if (const auto game = GetOwner()->GetParent()->GetComponent<Game>())
		game->gameEvent.RemoveObserver(this);
}

void Enemy::Start()
{
	m_pMoveComponent = GetOwner()->GetComponent<Move>();
	m_pMoveComponent->Animate(false);

	m_SpawnPos = m_pMoveComponent->GetMazePos();

	m_CurrentState = std::make_unique<SpawnState>(GetOwner());
	m_CurrentState->Enter();

	WallObservers(false);

	GetOwner()->GetParent()->GetComponent<Game>()->gameEvent.AddObserver(this);
}

void Enemy::Update()
{
 //                                                      if enemy class is notified by
 //                                                      wall shake -> switch to stun            
 //        Enemy State Machine                                +------------+                     
 //                                                           | Stun State |-------+             
 //                                                           +------------+       |             
 //                                                                 |              |             
 //                                                                 |              |             
 //                             game time is over 30 sec            |              v             
 //                                        |                        |       +------------+       
 //                                        |                        |       | Died State |       
 //                 +-----------------+    |   +------------+       |       +------------+       
 //                 | Ice Break State | <------| Move State |<------+              ^             
 //                 +-----------------+        +------------+                      |             
 //                         |                        ^                             |             
 //                         |                        |                             |             
 //game time is over 60 sec |                        |                     +--------------+      
 //and only 1 enemy remains |                        |                     | Pushed State |      
 //                         |                        |                     +--------------+      
 //                         v                        |                  if ice block detects     
 //                  +------------+         +-----------------+         enemy -> switch to pushed
 //                  | Flee State |-------->| (de)Spawn State |                                  
 //                  +------------+    |    +-----------------+                                  
 //                                    |                                                         
 //                            if enemy reached                                                  
 //                            corner -> de-spawn

	if (const auto newState = m_CurrentState->Update())
	{
		m_CurrentState->Exit();
		newState->Enter();
		m_CurrentState.reset(newState);
	}
}

void Enemy::Kill()
{
	m_CurrentState->Exit();

	if (const auto game = GetOwner()->GetParent()->GetComponent<Game>())
		game->gameEvent.RemoveObserver(this);

	WallObservers(true);
}

void Enemy::HandleEvent(real::GameObjectEvent event)
{
	if (event == real::GameObjectEvent::destroyed)
		enemyDied.Destroy();
}

void Enemy::HandleEvent(GameEvents event)
{
	switch (event)
	{
	case GameEvents::finished:
	case GameEvents::paused:
	{
		m_CurrentState->Exit();
		Disable();
		break;
	}
	case GameEvents::reset:
	{
		const auto pos = GetOwner()->GetParent()->GetComponent<Maze>()->GetNearestFreePos(m_SpawnPos);
		m_pMoveComponent->SetMazePos(pos);
		break;
	}
	case GameEvents::resumed:
	{
		m_CurrentState.reset(SwitchState<MoveState>());
		Enable();
		break;
	}
	}
}

void Enemy::HandleEvent(WallOrientation orientation)
{
	if (dynamic_cast<StunState*>(m_CurrentState.get()) != nullptr)
		return;

	const auto mazePos = m_pMoveComponent->GetMazePos();

	if (m_OrientationToPos[orientation].x == mazePos.x
		|| m_OrientationToPos[orientation].y == mazePos.y)
	{
		m_CurrentState->Exit();
		m_CurrentState.reset(new StunState(GetOwner()));
		m_CurrentState->Enter();
	}
}

void Enemy::Push(Direction direction)
{
	m_CurrentState->Exit();
	const auto newState = new PushedState(GetOwner());
	newState->SetDirection(direction);
	newState->Enter();
	m_CurrentState.reset(newState);

	m_pMoveComponent->SetMovementSpeed(PUSH_SPEED);
}

void Enemy::WallObservers(const bool remove)
{
	const auto maze = GetOwner()->GetParent()->GetComponent<Maze>();

	if (maze == nullptr)
		return;

	if (remove)
	{
		maze->GetWall(WallOrientation::north)->GetComponent<Wall>()->wallShaked.RemoveObserver(this);
		maze->GetWall(WallOrientation::east)->GetComponent<Wall>()->wallShaked.RemoveObserver(this);
		maze->GetWall(WallOrientation::south)->GetComponent<Wall>()->wallShaked.RemoveObserver(this);
		maze->GetWall(WallOrientation::west)->GetComponent<Wall>()->wallShaked.RemoveObserver(this);
	}
	else
	{
		maze->GetWall(WallOrientation::north)->GetComponent<Wall>()->wallShaked.AddObserver(this);
		maze->GetWall(WallOrientation::east)->GetComponent<Wall>()->wallShaked.AddObserver(this);
		maze->GetWall(WallOrientation::south)->GetComponent<Wall>()->wallShaked.AddObserver(this);
		maze->GetWall(WallOrientation::west)->GetComponent<Wall>()->wallShaked.AddObserver(this);
	}
}