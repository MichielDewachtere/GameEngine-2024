#ifndef ENEMY_H
#define ENEMY_H

#include <Subject.h>
#include <Component.h>
#include <glm/vec2.hpp>

#include "IEnemyState.h"

namespace dae
{
	enum class GameObjectEvent : char;
}

class Move;
enum class WallOrientation : char;
enum class Direction : char;
enum class GameEvents : char;

class Enemy final
	: public dae::Component
	, public dae::Observer<dae::GameObjectEvent>
	, public dae::Observer<GameEvents>
	, public dae::Observer<WallOrientation>
{
public:
	explicit Enemy(dae::GameObject* pOwner);
	virtual ~Enemy() override;

	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& rhs) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(Enemy&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;
	virtual void Kill() override;

	virtual void HandleEvent(dae::GameObjectEvent) override;
	virtual void HandleEvent(GameEvents) override;
	virtual void HandleEvent(WallOrientation) override;
	virtual void OnSubjectDestroy() override {}

	void Push(Direction direction);

	dae::Subject<> enemyDied;

private:
	std::unique_ptr<IEnemyState> m_CurrentState{};
	glm::ivec2 m_SpawnPos{};

	Move* m_pMoveComponent{ nullptr };

	template <typename T>
		requires std::is_base_of_v<IEnemyState, T>
	T* SwitchState();

	void WallObservers(bool remove);

	static std::map<WallOrientation, glm::ivec2> m_OrientationToPos;
};

template <typename T>
	requires std::is_base_of_v<IEnemyState, T>
T* Enemy::SwitchState()
{
	m_CurrentState->Exit();
	auto newState = new T(GetOwner());
	newState->Enter();
	return newState;
}

#endif // ENEMY_H
