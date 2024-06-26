﻿#ifndef TEXTURECOMPONENT_H
#define TEXTURECOMPONENT_H

#include <memory>
#include <glm/vec2.hpp>

#include "DrawableComponent.h"
#include "Texture2D.h"

namespace real
{
	//enum class TransformEvent : char;

	struct TextureInfo
	{
		std::unique_ptr<Texture2D> pTexture{ nullptr };
		glm::vec2 offset{ 0,0 };
	};

	class TextureComponent final : public DrawableComponent
	{
	public:
		//explicit TextureComponent(GameObject* pOwner, std::unique_ptr<Texture2D> pTexture = nullptr);
		//explicit TextureComponent(GameObject* pOwner, std::string texturePath = "");
		explicit TextureComponent(GameObject* pOwner, TextureInfo info = {});
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
		std::unique_ptr<Texture2D> m_pTexture;
		glm::vec2 m_TextureOffset;
	};
}

#endif // TEXTURECOMPONENT_H