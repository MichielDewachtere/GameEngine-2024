#ifndef BONUSTIME_H
#define BONUSTIME_H

#include <climits>
#include <Component.h>
#include <tuple>

class BonusTime final : public dae::Component
{
public:
	explicit BonusTime(dae::GameObject* pOwner);
	virtual ~BonusTime() override = default;

	BonusTime(const BonusTime& other) = delete;
	BonusTime& operator=(const BonusTime& rhs) = delete;
	BonusTime(BonusTime&& other) = delete;
	BonusTime& operator=(BonusTime&& rhs) = delete;

	virtual void Update() override;

private:
	bool m_BonusShown{ false }, m_TimeShown{ false };
	float m_AccuTime{ 0.f };

	static inline std::tuple<int, std::pair<int, int>, int> m_BonusToTime[] = {
		{1,{0,19}, 5000},
		{2,{20,29}, 2000},
		{3,{30,39}, 1000},
		{4,{40,49}, 500},
		{5,{50,59}, 10},
		{6,{60, INT_MAX}, 0}
	};
};

#endif // BONUSTIME_H