#ifndef TEXTFADEIN_H
#define TEXTFADEIN_H

#include <Component.h>
#include <string>

namespace real
{
	class TextComponent;
}

class TextFadeIn final : public real::Component
{
public:
	explicit TextFadeIn(real::GameObject* pOwner, std::string text);
	virtual ~TextFadeIn() override = default;

	TextFadeIn(const TextFadeIn& other) = delete;
	TextFadeIn& operator=(const TextFadeIn& rhs) = delete;
	TextFadeIn(TextFadeIn&& other) = delete;
	TextFadeIn& operator=(TextFadeIn&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

private:
	float m_AccuTime{ 0.f };
	size_t m_AccuChar{ 0 };
	std::string m_Text;
	real::TextComponent* m_pTextComponent{ nullptr };
};

#endif // TEXTFADEIN_H