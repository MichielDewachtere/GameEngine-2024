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
	inline static const std::string bonus_menu = "BonusMenu";
};

struct InputMaps
{
	inline static const std::string gameplay = "gameplay";
	inline static const std::string menu = "menu";
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