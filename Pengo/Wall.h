#ifndef WALL_H
#define WALL_H

#include <Component.h>
#include <Subject.h>

namespace dae
{
	class SpriteComponent;
}

class Wall final : public dae::Component
{
public:
	explicit Wall(dae::GameObject* pOwner);
	virtual ~Wall() override = default;

	Wall(const Wall& other) = delete;
	Wall& operator=(const Wall& rhs) = delete;
	Wall(Wall&& other) = delete;
	Wall& operator=(Wall&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void Shake();

	dae::Subject<float> wallShaked;

private:
	bool m_IsDirty{ false };
	float m_StunTime{ 5 };
	dae::SpriteComponent* m_pSpriteComponent{ nullptr };
};

#endif // WALL_H