#include "stdafx.h"
#include "InputMap.h"

dae::InputMap::InputMap(std::string name)
	: m_Name(std::move(name))
{
}

bool dae::InputMap::IsKeyCodeValid(int code)
{
	constexpr int minKeyBoardCode = 0;
	constexpr int maxKeyBoardCode = SDL_NUM_SCANCODES;

	return code > minKeyBoardCode && code < maxKeyBoardCode;
}
