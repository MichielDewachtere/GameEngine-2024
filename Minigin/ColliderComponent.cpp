#include "ColliderComponent.h"

#include "GameObject.h"
#include "Renderer.h"

dae::ColliderComponent::ColliderComponent(GameObject* pOwner, const glm::vec2& pos, const glm::vec2& size)
	: DrawableComponent(pOwner)
	, m_Position(pos)
	, m_Size(size)
{
}

dae::ColliderComponent::~ColliderComponent()
{
	const auto transform = GetOwner()->GetTransform();
	if (transform != nullptr)
		transform->worldPosChanged.RemoveObserver(this);
}

void dae::ColliderComponent::Start()
{
	const auto transform = GetOwner()->GetTransform();
	transform->worldPosChanged.AddObserver(this);

	const auto worldPos= transform->GetWorldPosition();
	m_OffsetFromParent = worldPos - m_Position;
}

void dae::ColliderComponent::DebugRender()
{
	if (m_DrawDebug)
	{
		Renderer::GetInstance().RenderRectangle(
			glm::ivec4{m_Position.x, m_Position.y, m_Size.x, m_Size.y}, 
			false,
			m_DebugColor
		);
	}
}

bool dae::ColliderComponent::IsOverlapping(const ColliderComponent& other) const
{
	if (GetOwner()->IsActive() == false || IsActive() == false)
		return false;

	const auto otherSize = other.GetSize();
	const auto otherPos = other.GetPosition();

	if (m_Position.x > otherPos.x + otherSize.x)
		return false;

	if (m_Position.x + m_Size.x < otherPos.x)
		return false;

	// Y(0,0) IS ON THE TOP RIGHT OF THE SCREEN
	if (m_Position.y > otherPos.y + otherSize.y)
		return false;

	if (m_Position.y + m_Size.y < otherPos.y)
		return false;

	return true;
}

bool dae::ColliderComponent::IsEntirelyOverlapping(const ColliderComponent& other, const glm::vec2& offset) const
{
	if (GetOwner()->IsActive() == false)
		return false;

	const auto otherSize = other.GetSize();
	const auto otherPos = other.GetPosition();

	auto pos = m_Position;
	pos.x -= offset.x / 2;
	pos.y -= offset.y / 2;

	auto size = m_Size;
	size.x += offset.x;
	size.y += offset.y;


	if (static_cast<int>(pos.x) >= static_cast<int>(otherPos.x)
		|| static_cast<int>(pos.x + size.x) <= static_cast<int>(otherPos.x + otherSize.x)
		// Y(0,0) IS ON THE TOP RIGHT OF THE SCREEN
		|| static_cast<int>(pos.y) >= static_cast<int>(otherPos.y)
		|| static_cast<int>(pos.y + size.y) <= static_cast<int>(otherPos.y + otherSize.y))
		return false;

	return true;

}

void dae::ColliderComponent::HandleEvent(TransformEvent, const glm::vec2& newPos)
{
	m_Position = newPos - m_OffsetFromParent;
}

void dae::ColliderComponent::OnSubjectDestroy()
{
	auto transform = GetOwner()->GetTransform();

	if (transform != nullptr)
		transform->worldPosChanged.RemoveObserver(this);
}
