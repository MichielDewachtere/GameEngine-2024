#ifndef ENEMY_H
#define ENEMY_H

#include <Subject.h>
#include <Component.h>
#include <glm/vec2.hpp>

#include "IEnemyState.h"

class Maze;

namespace real
{
	enum class GameObjectEvent : char;
}

class Move;
enum class WallOrientation : char;
enum class Direction : char;
enum class GameEvents : char;

class Enemy final
	: public real::Component
	, public real::Observer<real::GameObjectEvent>
	, public real::Observer<GameEvents>
	, public real::Observer<WallOrientation>
{
public:
	explicit Enemy(real::GameObject* pOwner);
	virtual ~Enemy() override;

	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& rhs) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(Enemy&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;
	virtual void Kill() override;

	virtual void HandleEvent(real::GameObjectEvent) override;
	virtual void HandleEvent(GameEvents) override;
	virtual void HandleEvent(WallOrientation) override;
	virtual void OnSubjectDestroy() override {}

	void Push(Direction direction);

	real::Subject<> enemyDied;

private:
	friend class EnemyPlayer;

	std::unique_ptr<IEnemyState> m_CurrentState{};
	glm::ivec2 m_SpawnPos{};

	Move* m_pMoveComponent{ nullptr };

	template <typename T, typename... Args>
		requires std::is_base_of_v<IEnemyState, T>
	T* SwitchState(Args... args);

	static void WallObservers(Observer<WallOrientation>* observer, Maze* maze, const bool remove);

	static void PushHelper(std::unique_ptr<IEnemyState>& state, Move& moveComponent, Direction direction);

	static std::map<WallOrientation, glm::ivec2> m_OrientationToPos;
};

template <typename T, typename... Args>
	requires std::is_base_of_v<IEnemyState, T>
T* Enemy::SwitchState(Args... args)
{
	m_CurrentState->Exit();
	auto newState = new T(GetOwner(), args...);
	newState->Enter();
	return newState;
}

#endif // ENEMY_H
