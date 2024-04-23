#ifndef STARTGAMECOMMAND_H
#define STARTGAMECOMMAND_H

#include <Command.h>

class StartGameCommand final : public real::Command
{
public:
	explicit StartGameCommand(int id, int controllerId);
	virtual ~StartGameCommand() override = default;

	StartGameCommand(const StartGameCommand& other) = delete;
	StartGameCommand& operator=(const StartGameCommand& rhs) = delete;
	StartGameCommand(StartGameCommand&& other) = delete;
	StartGameCommand& operator=(StartGameCommand&& rhs) = delete;

	virtual void Execute() override;
private:
	static inline bool m_IsFirstFrame{ true };
};

#endif // STARTGAMECOMMAND_H