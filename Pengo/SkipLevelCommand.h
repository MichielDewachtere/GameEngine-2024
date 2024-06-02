#ifndef SKIPLEVELCOMMAND_H
#define SKIPLEVELCOMMAND_H

#include <Command.h>

class SkipLevelCommand final : public real::Command
{
public:
	explicit SkipLevelCommand(int id, int controllerId);
	virtual ~SkipLevelCommand() override = default;

	SkipLevelCommand(const SkipLevelCommand& other) = delete;
	SkipLevelCommand& operator=(const SkipLevelCommand& rhs) = delete;
	SkipLevelCommand(SkipLevelCommand&& other) = delete;
	SkipLevelCommand& operator=(SkipLevelCommand&& rhs) = delete;

	void Execute() override;

private:
	int m_LastLevel{ -1 };
};

#endif // SKIPLEVELCOMMAND_H