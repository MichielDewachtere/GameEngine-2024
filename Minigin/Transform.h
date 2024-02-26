#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Component.h"

namespace dae
{
	class Transform final : public Component
	{
	public:
		explicit Transform(GameObject* pOwner) : Component(pOwner) {}
		explicit Transform(GameObject* pOwner, glm::vec3 localPos);
		virtual ~Transform() override = default;

		Transform(const Transform& other) = delete;
		Transform& operator=(const Transform& rhs) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(Transform&& rhs) = delete;

		const glm::vec2& GetLocalPosition();
		void SetLocalPosition(const glm::vec2& localPos);
		void SetLocalPosition(float x, float y);

		const glm::vec2& GetWorldPosition();
		void SetWorldPosition(const glm::vec2& );
		void SetWorldPosition(float x, float y);


	private:
		bool m_LocalNeedsUpdate{ true }, m_WorldNeedsUpdate{ true };
		glm::vec2 m_LocalPosition{}, m_WorldPosition{};
	};
}

#endif // TRANSFORM_H