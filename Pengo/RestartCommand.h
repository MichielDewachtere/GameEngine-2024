#ifndef RESTARTCOMMAND_H
#define RESTARTCOMMAND_H

#include <Command.h>

class RestartCommand final : public real::Command
{
public:
	explicit RestartCommand(int id, int controllerId);
	virtual ~RestartCommand() override = default;

	RestartCommand(const RestartCommand& other) = delete;
	RestartCommand& operator=(const RestartCommand& rhs) = delete;
	RestartCommand(RestartCommand&& other) = delete;
	RestartCommand& operator=(RestartCommand&& rhs) = delete;

	virtual void Execute() override;

};

#endif // RESTARTCOMMAND_H