#include "stdafx.h"
#include "TextureComponent.h"

#include "GameObject.h"
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
	const SDL_Rect rect{
		static_cast<int>(pos.x),
		static_cast<int>(pos.y),
		m_pTexture->GetSize().x,
		m_pTexture->GetSize().y
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
