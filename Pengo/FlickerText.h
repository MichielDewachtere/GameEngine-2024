#ifndef FLICKERTEXT_H
#define FLICKERTEXT_H

#include <Component.h>
#include <glm/vec4.hpp>

namespace real
{
	class TextComponent;
}

class FlickerText final : public real::Component
{
public:
	explicit FlickerText(real::GameObject* pOwner, glm::u8vec4 flickerColor, float flickerTime);
	virtual ~FlickerText() override = default;

	FlickerText(const FlickerText& other) = delete;
	FlickerText& operator=(const FlickerText& rhs) = delete;
	FlickerText(FlickerText&& other) = delete;
	FlickerText& operator=(FlickerText&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

private:
	float m_FlickerTime, m_AccuTime{ 0 };
	bool m_IsOriginal{ false };
	glm::u8vec4 m_OriginalColor{}, m_FlickerColor;
	real::TextComponent* m_pTextComponent{ nullptr };
};

#endif // FLICKERTEXT_H