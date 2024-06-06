#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "ColliderComponent.h"
#include "DrawableComponent.h"
#include "Observer.h"

namespace real
{
	enum class TransformEvent : char;

	struct ColliderInfo
	{
		glm::vec2 pos{ 0,0 };
		glm::vec2 size{ 0,0 };
		bool drawDebug{ true };
		glm::u8vec4 debugColor{ 0,255,0,255 };
	};

	class ColliderComponent final
		: public DrawableComponent
		, public Observer<TransformEvent, const glm::vec3&>
	{
	public:
		explicit ColliderComponent(GameObject* pOwner, ColliderInfo info = {});
		virtual ~ColliderComponent() override;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& rhs) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& rhs) = delete;

		void Start() override;
		void DebugRender() override;

		bool IsOverlapping(const ColliderComponent& other) const;
		bool IsEntirelyOverlapping(const ColliderComponent& other, const glm::vec2& = glm::vec2{ 0,0 }) const;

		glm::vec2 GetSize() const { return m_Size * m_Scale; }
		const glm::vec2& GetPosition() const { return m_Position; }

		void EnableDrawDebug(bool enable) { m_DrawDebug = enable; }
		void SetDebugColor(const glm::u8vec4& color) { m_DebugColor = color; }

		void HandleEvent(TransformEvent event, const glm::vec3& newPos) override;
		void OnSubjectDestroy() override;

	private:
		glm::vec2 m_Position, m_Size, m_OffsetFromParent{}, m_Scale{ 1,1 };
		bool m_DrawDebug;
		glm::u8vec4 m_DebugColor;
	};
}

#endif // COLLIDERCOMPONENT_H