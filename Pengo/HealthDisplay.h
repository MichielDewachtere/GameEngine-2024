#ifndef HEALTHDISPLAY_H
#define HEALTHDISPLAY_H

#include <cstdint>

#include <Component.h>

class HealthDisplay final : public real::Component
{
public:
	explicit HealthDisplay(real::GameObject* pOwner);
	virtual ~HealthDisplay() override = default;

	HealthDisplay(const HealthDisplay& other) = delete;
	HealthDisplay& operator=(const HealthDisplay& rhs) = delete;
	HealthDisplay(HealthDisplay&& other) = delete;
	HealthDisplay& operator=(HealthDisplay&& rhs) = delete;

	void AddLife();
	void RemoveLife();

private:
	uint8_t m_AmountOfLives{ 4 };

	void AddLifeTexture(int index) const;
};

#endif // HEALTHDISPLAY_H