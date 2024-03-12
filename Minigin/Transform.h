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

		virtual void Start() override;

		const glm::vec2& GetLocalPosition();
		void SetLocalPosition(const glm::vec2& localPos);
		void SetLocalPosition(float x, float y);

		const glm::vec2& GetWorldPosition();
		void SetWorldPosition(const glm::vec2& );
		void SetWorldPosition(float x, float y);

		void Translate(const glm::vec2&);
		void Translate(float x, float y);

		//const glm::vec2& GetPivot() const { return m_Pivot; }
		//void SetPivot(const glm::vec2& pivot) { m_Pivot = pivot; }
		//void SetPivot(float x, float y) { SetPivot({ x,y }); }

		//const float GetRotation() const { return m_Rotation; }
		//void SetRotation(float rotation);
		//void IncrementRotation(const float amount);
		//void DecrementRotation(const float amount);

	private:
		bool m_LocalNeedsUpdate{ true }, m_WorldNeedsUpdate{ true };
		glm::vec2 m_LocalPosition{}, m_WorldPosition{}/*, m_Pivot{}*/;
		//float m_Rotation{ 0.f };
	};
}

#endif // TRANSFORM_H