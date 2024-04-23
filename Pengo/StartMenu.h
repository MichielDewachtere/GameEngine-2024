#ifndef STARTMENU_H
#define STARTMENU_H

#include <Scene.h>
#include <RealEngine.h>

class StartMenu final : public real::Scene
{
public:
	explicit StartMenu(std::string name, std::string inputMap, real::WindowSettings settings);
	virtual ~StartMenu() override = default;

	StartMenu(const StartMenu& other) = delete;
	StartMenu& operator=(const StartMenu& rhs) = delete;
	StartMenu(StartMenu&& other) = delete;
	StartMenu& operator=(StartMenu&& rhs) = delete;

	virtual void Load() override;

private:
	real::WindowSettings m_Settings;
};

#endif // STARTMENU_H