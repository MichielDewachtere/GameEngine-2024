#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "ColliderComponent.h"
#include "DrawableComponent.h"
#include "Observer.h"

namespace dae
{
	enum class TransformEvent : char;

	class ColliderComponent final
		: public DrawableComponent
		, public Observer<TransformEvent, const glm::vec2&>
	{
	public:
		explicit ColliderComponent(GameObject* pOwner, const glm::vec2& pos, const glm::vec2& size);
		virtual ~ColliderComponent() override;

		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(const ColliderComponent& rhs) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& rhs) = delete;

		void Start() override;
		void DebugRender() override;

		bool IsOverlapping(const ColliderComponent& other) const;
		bool IsEntirelyOverlapping(const ColliderComponent& other, const glm::vec2& = glm::vec2{ 0,0 }) const;

		const glm::vec2& GetSize() const { return m_Size; }
		const glm::vec2& GetPosition() const { return m_Position; }

		void EnableDrawDebug(bool enable) { m_DrawDebug = enable; }
		void SetDebugColor(const glm::u8vec4& color) { m_DebugColor = color; }

		void HandleEvent(TransformEvent event, const glm::vec2& newPos) override;
		void OnSubjectDestroy() override;

	private:
		glm::vec2 m_Position, m_Size, m_OffsetFromParent{}, m_Scale{ 1,1 };
		bool m_DrawDebug{ false };
		glm::u8vec4 m_DebugColor{ 0,255,0,255 };
	};
}

#endif // COLLIDERCOMPONENT_H