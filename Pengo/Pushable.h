#ifndef PUSHABLE_H
#define PUSHABLE_H

#include <Component.h>

class Maze;
class Move;
enum class Direction : char;

class Pushable final : public dae::Component
{
public:
	explicit Pushable(dae::GameObject* pOwner);
	virtual ~Pushable() override = default;

	Pushable(const Pushable& other) = delete;
	Pushable& operator=(const Pushable& rhs) = delete;
	Pushable(Pushable&& other) = delete;
	Pushable& operator=(Pushable&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void Push(Direction direction);
	bool IsBeingPushed() const;

private:
	bool m_Pushed{ false };
	Direction m_Direction{};
	Move* m_pMoveComponent{ nullptr };
	Maze* m_pMazeComponent{ nullptr };
};

#endif // PUSHABLE_H