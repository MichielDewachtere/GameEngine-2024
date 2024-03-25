#include "TextureComponent.h"

#include <SDL_rect.h>

#include "GameObject.h"
#include "Logger.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(GameObject* pOwner, std::unique_ptr<Texture2D> pTexture)
	: DrawableComponent(pOwner)
	, m_pTexture(std::move(pTexture))
{
}

//dae::TextureComponent::TextureComponent(GameObject* pOwner, std::string texturePath)
//	: DrawableComponent(pOwner)
//{
//	m_pTexture = ResourceManager::GetInstance().LoadTexture(std::move(texturePath));
//}

void dae::TextureComponent::Render()
{
	if (m_pTexture == nullptr)
		Logger::LogWarning({ "No texture found in texture component" });


	const auto pos = GetOwner()->GetTransform()->GetWorldPosition() - m_TextureOffset;
	const auto size = glm::vec2(m_pTexture->GetSize()) * GetOwner()->GetTransform()->GetScale();

	const SDL_Rect rect{
		static_cast<int>(pos.x),
		static_cast<int>(pos.y),
		static_cast<int>(size.x),
		static_cast<int>(size.y)
	};
	Renderer::GetInstance().RenderTexture(*m_pTexture, rect);
}

dae::Texture2D* dae::TextureComponent::GetTexture() const
{
	if (m_pTexture == nullptr)
	{
		Logger::LogWarning({ "No texture found in texture component" });
		return nullptr;
	}

	return m_pTexture.get();
}
