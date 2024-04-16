#ifndef PUSHABLE_H
#define PUSHABLE_H

#include <Component.h>
#include <vector>

#include "Player.h"
#include "Subject.h"

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
	std::vector<real::GameObject*> m_EnemiesPushed{};
	PlayerNumber m_PushedBy{};
	Direction m_Direction{};
	Move* m_pMoveComponent{ nullptr };
	Maze* m_pMazeComponent{ nullptr };
};

#endif // PUSHABLE_H