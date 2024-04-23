#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include <Scene.h>

class GameOverMenu final : public real::Scene
{
public:
	explicit GameOverMenu(std::string name, std::string inputMap);
	virtual ~GameOverMenu() override = default;

	GameOverMenu(const GameOverMenu& other) = delete;
	GameOverMenu& operator=(const GameOverMenu& rhs) = delete;
	GameOverMenu(GameOverMenu&& other) = delete;
	GameOverMenu& operator=(GameOverMenu&& rhs) = delete;

	virtual void Load() override;

private:
	
};

#endif // GAMEOVERMENU_H