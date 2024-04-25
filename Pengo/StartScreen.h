#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <Component.h>

enum class Modes : char;

class StartScreen final : public real::Component
{
public:
	explicit StartScreen(real::GameObject* pOwner);
	virtual ~StartScreen() override = default;

	StartScreen(const StartScreen& other) = delete;
	StartScreen& operator=(const StartScreen& rhs) = delete;
	StartScreen(StartScreen&& other) = delete;
	StartScreen& operator=(StartScreen&& rhs) = delete;

	void ModeSelected(Modes);
	void PlayerSelected();

private:
	enum class State : char
	{
		selectMode,
		selectPlayers,
		start
	};

	State m_CurrentState{ State::selectMode };
	int m_AmountOfPlayersToRegister{ 0 };

	void AddPlayerText(int offset, bool isEnemy, int playerId) const;
};

#endif // STARTSCREEN_H