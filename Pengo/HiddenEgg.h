#ifndef HIDDENEGG_H
#define HIDDENEGG_H

#include <Component.h>

namespace dae
{
	class SpriteComponent;
}

class HiddenEgg final : public dae::Component
{
public:
	explicit HiddenEgg(dae::GameObject* pOwner);
	virtual ~HiddenEgg() override;

	HiddenEgg(const HiddenEgg& other) = delete;
	HiddenEgg& operator=(const HiddenEgg& rhs) = delete;
	HiddenEgg(HiddenEgg&& other) = delete;
	HiddenEgg& operator=(HiddenEgg&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void PopEgg();

private:
	bool m_EggPopped{ false };
	dae::SpriteComponent* m_pSpriteComponent{ nullptr };
};

#endif // HIDDENEGG_H