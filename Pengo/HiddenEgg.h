#ifndef HIDDENEGG_H
#define HIDDENEGG_H

#include <Component.h>
#include <type_traits>

namespace real
{
	class SpriteComponent;
}

class HiddenEgg final : public real::Component
{
public:
	explicit HiddenEgg(real::GameObject* pOwner);
	virtual ~HiddenEgg() override;

	HiddenEgg(const HiddenEgg& other) = delete;
	HiddenEgg& operator=(const HiddenEgg& rhs) = delete;
	HiddenEgg(HiddenEgg&& other) = delete;
	HiddenEgg& operator=(HiddenEgg&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void PopEgg();
	void BreakEgg();

private:
	enum class EggBreakSequence : char
	{
		iceBreakAnim = 0,
		eggFlashAnim = 1,
		eggBreakAnim = 2,
		destroyEgg = 3
	};
	bool m_EggPopped{ false };
	EggBreakSequence m_CurrentState{ EggBreakSequence::iceBreakAnim };
	real::SpriteComponent* m_pSpriteComponent{ nullptr }, * m_IceBlockSpriteComponent{ nullptr };
};

#endif // HIDDENEGG_H