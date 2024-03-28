#ifndef INTERACTCOMPONENT_H
#define INTERACTCOMPONENT_H

#include <Component.h>

enum class Direction : char;

namespace dae
{
	class SpriteComponent;
}

class Move;
class Maze;

class Interact final : public dae::Component
{
public:
	explicit Interact(dae::GameObject* pOwner);
	virtual ~Interact() override = default;

	Interact(const Interact& other) = delete;
	Interact& operator=(const Interact& rhs) = delete;
	Interact(Interact&& other) = delete;
	Interact& operator=(Interact&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void AttemptInteraction();

private:
	Maze* m_pMaze{ nullptr };
	Move* m_pMove{ nullptr };
	dae::SpriteComponent* m_pSpriteComponent{ nullptr };

	bool m_IsAnimating{ false };

	void Animate(Direction dir);
};

#endif // INTERACTCOMPONENT_H