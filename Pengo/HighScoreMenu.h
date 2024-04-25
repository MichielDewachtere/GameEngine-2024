#ifndef HIGHSCOREMENU_H
#define HIGHSCOREMENU_H

#include <Scene.h>
#include <RealEngine.h>

class HighScoreMenu final : public real::Scene
{
public:
	explicit HighScoreMenu(std::string name, std::string inputMap, real::WindowSettings settings);
	virtual ~HighScoreMenu() override = default;

	HighScoreMenu(const HighScoreMenu& other) = delete;
	HighScoreMenu& operator=(const HighScoreMenu& rhs) = delete;
	HighScoreMenu(HighScoreMenu&& other) = delete;
	HighScoreMenu& operator=(HighScoreMenu&& rhs) = delete;

	virtual void Load() override;

private:
	real::WindowSettings m_Settings;
};

#endif // HIGHSCOREMENU_H