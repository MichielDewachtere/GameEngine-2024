#ifndef BONUSTIMEMENU_H
#define BONUSTIMEMENU_H

#include <Scene.h>
#include <Minigin.h>

class BonusTimeMenu final : public dae::Scene
{
public:
	explicit BonusTimeMenu(std::string name, std::string inputMap, dae::WindowSettings settings);
	virtual ~BonusTimeMenu() override = default;

	BonusTimeMenu(const BonusTimeMenu& other) = delete;
	BonusTimeMenu& operator=(const BonusTimeMenu& rhs) = delete;
	BonusTimeMenu(BonusTimeMenu&& other) = delete;
	BonusTimeMenu& operator=(BonusTimeMenu&& rhs) = delete;

	virtual void Load() override;

private:
	dae::WindowSettings m_Settings;

	void WriteLine(dae::GameObject& go, int i, std::string text) const;
};

#endif // BONUSTIMEMENU_H