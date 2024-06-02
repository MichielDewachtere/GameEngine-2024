#include "MuteCommand.h"

#include "Locator.h"

MuteCommand::MuteCommand(int id, int controllerId)
	: Command(id, controllerId)
{
}

void MuteCommand::Execute()
{
	m_IsMuted = !m_IsMuted;
	real::Locator::GetAudioSystem().Mute(m_IsMuted);
}
