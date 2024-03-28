#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <stdint.h>

struct Tags
{
	
};

struct Scenes
{
	
};

struct InputMaps
{
	
};

struct InputCommands
{
	inline static constexpr uint8_t move_up = 0;
	inline static constexpr uint8_t move_down = 1;
	inline static constexpr uint8_t move_left = 2;
	inline static constexpr uint8_t move_right = 3;
	inline static constexpr uint8_t interact = 4;
};

#endif // GAMEINFO_H