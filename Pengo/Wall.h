#ifndef WALL_H
#define WALL_H

#include <Component.h>
#include <Subject.h>

class Maze;

namespace real
{
	class SpriteComponent;
}

enum class WallOrientation : char;

class Wall final : public real::Component
{
public:
	explicit Wall(real::GameObject* pOwner, WallOrientation orientation);
	virtual ~Wall() override = default;

	Wall(const Wall& other) = delete;
	Wall& operator=(const Wall& rhs) = delete;
	Wall(Wall&& other) = delete;
	Wall& operator=(Wall&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void Shake();

	real::Subject<WallOrientation> wallShaked;

private:
	bool m_IsDirty{ false };
	WallOrientation m_Orientation;

	Maze* m_pMazeComponent{ nullptr };
	real::SpriteComponent* m_pSpriteComponent{ nullptr };
};

#endif // WALL_H