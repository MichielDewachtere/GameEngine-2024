#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include "DrawableComponent.h"
#include "Texture2D.h"

namespace dae
{
	class TextureComponent final : public DrawableComponent
	{
	public:
		explicit TextureComponent(GameObject* pOwner, std::unique_ptr<Texture2D> pTexture = nullptr);
		//explicit TextureComponent(GameObject* pOwner, std::string texturePath = "");
		virtual ~TextureComponent() override = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent& operator=(const TextureComponent& rhs) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(TextureComponent&& rhs) = delete;

		void Update() override {}
		void Render() override;

		void SetTexture(std::unique_ptr<Texture2D> pTexture) { m_pTexture = std::move(pTexture); }
		Texture2D* GetTexture() const;

		void SetRenderOffset(const glm::vec2 offset) { m_TextureOffset = offset; }
		void SetRenderOffset(int x, int y) { SetRenderOffset({ x,y }); }
		glm::vec2 GetRenderOffset() const { return m_TextureOffset; }


	private:
		std::unique_ptr<Texture2D> m_pTexture{ nullptr };
		glm::vec2 m_TextureOffset{ 0,0 };
	};
}

#endif // TEXTURECOMPONENT_H