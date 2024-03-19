#ifndef LOADNEWSCENECOMMAND_H
#define LOADNEWSCENECOMMAND_H

#include "Command.h"

class LoadSceneCommand final : public dae::Command
{
public:
	explicit LoadSceneCommand(int id, int controllerId, std::string sceneName);
	virtual ~LoadSceneCommand() override = default;

	LoadSceneCommand(const LoadSceneCommand& other) = delete;
	LoadSceneCommand& operator=(const LoadSceneCommand& rhs) = delete;
	LoadSceneCommand(LoadSceneCommand&& other) = delete;
	LoadSceneCommand& operator=(LoadSceneCommand&& rhs) = delete;

	virtual void Execute() override;

private:
	std::string m_Name;
};

#endif // LOADNEWSCENECOMMAND_H