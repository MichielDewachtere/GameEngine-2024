#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <cstdint>
#include <Audio.h>

struct Tags
{
	inline static const std::string pengo = "Player";
	inline static const std::string sno_bee = "Enemy";
	inline static const std::string game = "Game";
};

struct Scenes
{
	inline static const std::string start_menu = "StartMenu";
	inline static const std::string bonus_menu = "BonusMenu";
	inline static const std::string game_over_menu = "GameOverMenu";
};

struct InputMaps
{
	inline static const std::string gameplay = "gameplay";
	inline static const std::string start_menu = "start_menu";
	inline static const std::string bonus_time_menu = "bonus_time_menu";
	inline static const std::string game_over_menu = "game_over_menu";
};

struct InputCommands
{
	// StartScreen
	inline static constexpr uint8_t mode_go_up = 0;
	inline static constexpr uint8_t mode_go_down = 1;
	inline static constexpr uint8_t mode_confirm = 2;
	inline static constexpr uint8_t player_join = 3;
	inline static constexpr uint8_t name_character_confirm = 4;
	inline static constexpr uint8_t name_character_up = 5;
	inline static constexpr uint8_t name_character_down = 6;
	inline static constexpr uint8_t start = 7;

	// GamePlay
	inline static constexpr uint8_t move_up = 0;
	inline static constexpr uint8_t move_down = 1;
	inline static constexpr uint8_t move_left = 2;
	inline static constexpr uint8_t move_right = 3;
	inline static constexpr uint8_t interact = 4;

	inline static constexpr uint8_t print_maze = 100;
};

struct Sounds
{
	inline static const real::Sound test = { 1, 128, 0, -1,
		"../data/audio/block_stopped.mp3" };
	inline static const real::Sound game_music = { 1, 32, -1, 1,
		"../data/audio/popcorn.mp3" };
};

#endif // GAMEINFO_H