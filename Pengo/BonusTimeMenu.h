#ifndef BONUSTIMEMENU_H
#define BONUSTIMEMENU_H

#include <Scene.h>
#include <RealEngine.h>

class BonusTimeMenu final : public real::Scene
{
public:
	explicit BonusTimeMenu(std::string name, std::string inputMap, real::WindowSettings settings);
	virtual ~BonusTimeMenu() override = default;

	BonusTimeMenu(const BonusTimeMenu& other) = delete;
	BonusTimeMenu& operator=(const BonusTimeMenu& rhs) = delete;
	BonusTimeMenu(BonusTimeMenu&& other) = delete;
	BonusTimeMenu& operator=(BonusTimeMenu&& rhs) = delete;

	virtual void Load() override;

private:
	real::WindowSettings m_Settings;

	void WriteLine(real::GameObject& go, int i, std::string text) const;
};

#endif // BONUSTIMEMENU_H