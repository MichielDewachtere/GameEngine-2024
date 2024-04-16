#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <memory>
#include <vector>
#include <glm/vec4.hpp>

#include "DrawableComponent.h"
#include "Observer.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Transform.h"

namespace real
{
	struct SpriteSheet
	{
		std::unique_ptr<Texture2D> pTexture{};
		int rows{}, columns{};
		float timePerAnimation{};
	};


	class SpriteComponent final
		: public DrawableComponent
		, public Observer<TransformEvent, const glm::vec2&>
	{
	public:
		explicit SpriteComponent(GameObject* pOwner, SpriteSheet spriteSheet);
		virtual ~SpriteComponent() override;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& rhs) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& rhs) = delete;

		virtual void Update() override;
		virtual void Render() override;

		void HandleEvent(TransformEvent, const glm::vec2&) override;
		void OnSubjectDestroy() override;

		void SelectSprite(int idx);

		void PlayAnimation(int startIdx, int endIdx, int loops = -1, float timePerAnimation = 0);
		void PlayAnimation(const std::vector<int>& idcs, int loops = -1, float timePerAnimation = 0);
		void UpdateAnimation(int startIdx, int endIdx, int loops = -1, float timePerAnimation = 0);
		bool IsAnimationPlaying() const { return m_IsAnimationPlaying; }

		void Pause(bool value);
		bool IsPaused() const { return m_Pause; }
		void Stop(bool value);

		void FlipTexture(RenderFlip flip);

		glm::ivec2 GetSpriteSheetSize() const;
		glm::ivec2 GetSpriteSize() const;

	private:
		SpriteSheet m_SpriteSheet;

		int m_CurrIdx{};
		int m_StartIdx{};
		int m_EndIdx{};
		bool m_PlaySelectedIdcs{};
		std::vector<int> m_SelectedIdcs{};

		int m_Loops{};
		int m_AccuLoops{};

		float m_AccuTime{};
		float m_TimePerAnimation{};

		bool m_Pause{};
		bool m_IsAnimationPlaying{};
		bool m_Stop{};

		glm::vec2 m_RenderPos{};
		glm::ivec4 m_Rect{};
		RenderFlip m_Flip{ RenderFlip::none };
	};
}

#endif // SPRITECOMPONENT_H