#ifndef PUSHABLE_H
#define PUSHABLE_H

#include <Component.h>
#include <vector>
#include <glm/vec2.hpp>

#include "Player.h"
#include "Subject.h"

namespace real
{
	class ColliderComponent;
}

class Maze;
class Move;
enum class Direction : char;

class Pushable final : public real::Component
{
public:
	explicit Pushable(real::GameObject* pOwner);
	virtual ~Pushable() override = default;

	Pushable(const Pushable& other) = delete;
	Pushable& operator=(const Pushable& rhs) = delete;
	Pushable(Pushable&& other) = delete;
	Pushable& operator=(Pushable&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void Push(Direction direction, PlayerNumber pushedBy = PlayerNumber::none);
	bool IsBeingPushed() const;

	real::Subject<int> enemiesCrushed;

private:
	bool m_Pushed{ false };
	std::vector<real::GameObject*> m_EnemiesPushed{}, m_EnemiesToPush{};
	PlayerNumber m_PushedBy{};
	Direction m_Direction{};
	Move* m_pMoveComponent{ nullptr };
	Maze* m_pMazeComponent{ nullptr };
	real::ColliderComponent* m_pColliderComponent{ nullptr };

	void LookForEnemies();
	void PushEnemies();
	void AddPoints();

	real::ColliderComponent* GenerateTempColliderComponent() const;

	static std::map<Direction, glm::ivec2> m_DirectionToOffset;
};

#endif // PUSHABLE_H