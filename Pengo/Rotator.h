#ifndef ROTATOR_H
#define ROTATOR_H

#include <glm/vec2.hpp>

#include "Component.h"

class Rotator final : public dae::Component
{
public:
	explicit Rotator(dae::GameObject* pOwner, glm::vec2 pivot, float rotationSpeed);
	virtual ~Rotator() override = default;

	Rotator(const Rotator& other) = delete;
	Rotator& operator=(const Rotator& rhs) = delete;
	Rotator(Rotator&& other) = delete;
	Rotator& operator=(Rotator&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

private:
	glm::vec2 m_Pivot;
	float m_RotationSpeed, m_Rotation, m_Distance{};
};

#endif // ROTATOR_H