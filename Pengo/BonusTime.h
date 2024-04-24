#ifndef BONUSTIME_H
#define BONUSTIME_H

#include <climits>
#include <Component.h>
#include <tuple>

#include "ScoreDisplay.h"

class BonusTime final : public real::Component
{
public:
	explicit BonusTime(real::GameObject* pOwner);
	virtual ~BonusTime() override = default;

	BonusTime(const BonusTime& other) = delete;
	BonusTime& operator=(const BonusTime& rhs) = delete;
	BonusTime(BonusTime&& other) = delete;
	BonusTime& operator=(BonusTime&& rhs) = delete;

	virtual void Update() override;

private:
	bool m_BonusShown{ false }, m_TimeShown{ false };
	float m_AccuTime{ 0.f };

	static inline std::tuple<int, std::pair<int, int>, ScoreEvents> m_BonusToTime[] = {
		{1,{0,19}, ScoreEvents::bonusTimeUnder20},
		{2,{20,29}, ScoreEvents::bonusTimeUnder30},
		{3,{30,39}, ScoreEvents::bonusTimeUnder40},
		{4,{40,49}, ScoreEvents::bonusTimeUnder50},
		{5,{50,59}, ScoreEvents::bonusTimeUnder60},
		{6,{60, INT_MAX}, ScoreEvents::null}
	};
};

#endif // BONUSTIME_H