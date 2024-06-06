#include "ColliderComponent.h"

#include "GameObject.h"
#include "Renderer.h"

real::ColliderComponent::ColliderComponent(GameObject* pOwner, ColliderInfo info)
	: DrawableComponent(pOwner)
	, m_Position(info.pos)
	, m_Size(info.size)
	, m_DrawDebug(info.drawDebug)
	, m_DebugColor(info.debugColor)
{
}

real::ColliderComponent::~ColliderComponent()
{
	const auto transform = GetOwner()->GetTransform();
	if (transform != nullptr)
	{
		transform->worldPosChanged.RemoveObserver(this);
		transform->scaleChanged.RemoveObserver(this);
	}
}

void real::ColliderComponent::Start()
{
	const auto transform = GetOwner()->GetTransform();
	transform->worldPosChanged.AddObserver(this);
	transform->scaleChanged.AddObserver(this);

	const glm::vec2 worldPos= transform->GetWorldPosition();
	m_OffsetFromParent = worldPos - m_Position;
	m_Scale = transform->GetScale();
}

void real::ColliderComponent::DebugRender()
{
#ifndef NDEBUG
	if (m_DrawDebug)
	{
		Renderer::GetInstance().RenderRectangle(
			glm::ivec4{m_Position.x, m_Position.y, m_Size.x * m_Scale.x, m_Size.y * m_Scale.y },
			false,
			m_DebugColor
		);
	}
#endif
}

bool real::ColliderComponent::IsOverlapping(const ColliderComponent& other) const
{
	if (GetOwner() && (GetOwner()->IsActive() == false || IsActive() == false))
		return false;

	const auto otherSize = other.GetSize();
	const auto otherPos = other.GetPosition();

	const auto size = m_Size * m_Scale;

	if (m_Position.x > otherPos.x + otherSize.x)
		return false;

	if (m_Position.x + size.x < otherPos.x)
		return false;

	// Y(0,0) IS ON THE TOP RIGHT OF THE SCREEN
	if (m_Position.y > otherPos.y + otherSize.y)
		return false;

	if (m_Position.y + size.y < otherPos.y)
		return false;

	return true;
}

bool real::ColliderComponent::IsEntirelyOverlapping(const ColliderComponent& other, const glm::vec2& offset) const
{
	if (GetOwner() && (GetOwner()->IsActive() == false || IsActive() == false))
		return false;

	const auto otherSize = other.GetSize();
	const auto otherPos = other.GetPosition();

	auto pos = m_Position;
	pos.x -= offset.x / 2;
	pos.y -= offset.y / 2;

	auto size = m_Size * m_Scale;
	size.x += offset.x;
	size.y += offset.y;

	//if (pos.x < otherPos.x ||
	//	pos.x + size.x > otherPos.x + otherSize.x ||
	//	pos.y < otherPos.y ||
	//	pos.y + size.y > otherPos.y + otherSize.y)
	//	return false;
	//
	if (static_cast<int>(pos.x) >= static_cast<int>(otherPos.x)
		|| static_cast<int>(pos.x + size.x) <= static_cast<int>(otherPos.x + otherSize.x)
		// Y(0,0) IS ON THE TOP RIGHT OF THE SCREEN
		|| static_cast<int>(pos.y) >= static_cast<int>(otherPos.y)
		|| static_cast<int>(pos.y + size.y) <= static_cast<int>(otherPos.y + otherSize.y))
		return false;

	return true;

}

void real::ColliderComponent::HandleEvent(TransformEvent event, const glm::vec3& data)
{
	if (event == TransformEvent::worldPosChanged)
		m_Position = glm::vec2{ data } - m_OffsetFromParent;
	else if (event == TransformEvent::scaleChanged)
		m_Scale = data;
}

void real::ColliderComponent::OnSubjectDestroy()
{
	const auto transform = GetOwner()->GetTransform();

	if (transform != nullptr)
	{
		transform->worldPosChanged.RemoveObserver(this);
		transform->scaleChanged.RemoveObserver(this);
	}
}
