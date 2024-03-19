#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include <stdint.h>

#include <Component.h>

namespace dae
{
	class TextComponent;
}

class FPSCounter final : public dae::Component
{
public:
	explicit FPSCounter(dae::GameObject* pOwner);
	virtual ~FPSCounter() override = default;

	FPSCounter(const FPSCounter& other) = delete;
	FPSCounter& operator=(const FPSCounter& rhs) = delete;
	FPSCounter(FPSCounter&& other) = delete;
	FPSCounter& operator=(FPSCounter&& rhs) = delete;

	virtual void Update() override;
	virtual void Start() override;

private:
	uint32_t m_PreviousFPS{ 0 };
	dae::TextComponent* m_pTextComponent{ nullptr };
};

#endif // FPSCOUNTER_H