#ifndef COLLIDERTEST_H
#define COLLIDERTEST_H

#include "ColliderComponent.h"
#include "Component.h"

class ColliderTest final : public dae::Component
{
public:
	explicit ColliderTest(dae::GameObject* pOwner);
	~ColliderTest() override = default;

	ColliderTest(const ColliderTest& other) = delete;
	ColliderTest& operator=(const ColliderTest& rhs) = delete;
	ColliderTest(ColliderTest&& other) = delete;
	ColliderTest& operator=(ColliderTest&& rhs) = delete;

	void Start() override;
	void Update() override;

	void SetColliderToCheck(dae::ColliderComponent* pOther);

private:
	dae::ColliderComponent* m_Self{ nullptr }, *m_pOther{ nullptr };
};

#endif // COLLIDERTEST_H