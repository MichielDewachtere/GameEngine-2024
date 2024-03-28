#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <stdint.h>

struct Tags
{
	inline static const std::string pengo = "Player";
	inline static const std::string sno_bee = "Enemy";
	inline static const std::string game = "Game";
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

	inline static constexpr uint8_t print_maze = 100;
};

#endif // GAMEINFO_H