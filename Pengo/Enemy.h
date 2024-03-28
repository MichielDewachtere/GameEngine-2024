#ifndef ENEMY_H
#define ENEMY_H

#include <Subject.h>
#include <Component.h>


namespace dae
{
	enum class GameObjectEvent : char;
	class SpriteComponent;
}

class Pushable;
enum class Direction : char;
enum class GameEvents : bool;
class Move;

class Enemy final
	: public dae::Component
	, public dae::Observer<dae::GameObjectEvent>
{
public:
	enum class EnemyState
	{
		spawned = 0,
		moving = 1,
		pushed = 2,
		stunned = 3,
		died = 4
	};

public:
	explicit Enemy(dae::GameObject* pOwner);
	virtual ~Enemy() override;

	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& rhs) = delete;
	Enemy(Enemy&& other) = delete;
	Enemy& operator=(Enemy&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	virtual void HandleEvent(dae::GameObjectEvent) override;
	virtual void OnSubjectDestroy() override {}

	void Push(Direction direction);

	dae::Subject<> enemyDied;

private:
	EnemyState m_CurrentState{ EnemyState::spawned };
	dae::SpriteComponent* m_pSpriteComponent{ nullptr };
	Move* m_pMoveComponent{ nullptr };
	Pushable* m_PushableComponent{ nullptr };

	Direction m_PushDirection{};
	static std::map<Direction, std::pair<int, int>> m_DirectionToSquashAnim;
};

#endif // ENEMY_H