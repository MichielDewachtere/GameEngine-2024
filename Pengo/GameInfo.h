#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <cstdint>
#include <Audio.h>

#include "Macros.h"

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
	inline static const std::string high_score_menu = "HighScoreMenu";
	inline static const std::string game_over_menu = "GameOverMenu";
};

struct InputMaps
{
	inline static const std::string gameplay = "gameplay";
	inline static const std::string start_menu = "start_menu";
	inline static const std::string bonus_time_menu = "bonus_time_menu";
	inline static const std::string high_score_menu = "high_score_menu";
	inline static const std::string game_over_menu = "game_over_menu";
};

struct InputCommands
{
	// StartScreen
	inline static constexpr uint8_t mode_go_up = 0;
	inline static constexpr uint8_t mode_go_down = 1;
	inline static constexpr uint8_t mode_confirm = 2;
	inline static constexpr uint8_t player_join = 3;
	inline static constexpr uint8_t start = 7;

	// HighScore Screen
	inline static constexpr uint8_t name_character_confirm = 4;
	inline static constexpr uint8_t name_character_up = 5;
	inline static constexpr uint8_t name_character_down = 6;

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
	inline static const real::Sound act_clear = { 1, VOLUME, 0, 1,
	"../data/audio/act_clear.mp3" };
	inline static const real::Sound act_start = { 1, VOLUME, 0, 1,
	"../data/audio/act_start.mp3" };
	inline static const real::Sound block_stopped = { 1, VOLUME, 0, -1,
	"../data/audio/block_stopped.mp3" };
	inline static const real::Sound counting_bonus_points = { 1, VOLUME, 0, -1,
	"../data/audio/counting_bonus_points.mp3" };
	inline static const real::Sound credit_sound = { 1, VOLUME, 0, -1,
	"../data/audio/credit_sound.mp3" };
	inline static const real::Sound diamond_block_bonus = { 1, VOLUME, 0, -1,
	"../data/audio/diamond_block_bonus.mp3" };
	inline static const real::Sound drawing_maze = { 1, VOLUME, 0, -1,
	"../data/audio/drawing_maze.mp3" };
	inline static const real::Sound egg_destroyed = { 1, VOLUME, 0, -1,
	"../data/audio/egg_destroyed.mp3" };
	inline static const real::Sound ice_destroyed = { 1, VOLUME, 0, -1,
	"../data/audio/ice_destroyed.mp3" };
	inline static const real::Sound intermission = { 1, VOLUME, 0, -1,
	"../data/audio/intermission.mp3" };
	inline static const real::Sound killed = { 1, VOLUME, 0, 1,
	"../data/audio/killed.mp3" };
	inline static const real::Sound last_sno_bee = { 1, VOLUME, 0, -1,
	"../data/audio/last_sno_bee.mp3" };
	inline static const real::Sound miss = { 1, VOLUME, 0, -1,
	"../data/audio/miss.mp3" };
	inline static const real::Sound name_entry = { 1, VOLUME, -1, 1,
	"../data/audio/name_entry.mp3" };
	inline static const real::Sound popcorn = { 1, VOLUME, -1, 1,
	"../data/audio/popcorn.mp3" };
	inline static const real::Sound popcorn_fast = { 1, VOLUME, -1, 1,
	"../data/audio/popcorn_fast.mp3" };
	inline static const real::Sound popcorn_faster = { 1, VOLUME, -1, 1,
	"../data/audio/popcorn_faster.mp3" };
	inline static const real::Sound push_ice = { 1, VOLUME, 0, -1,
	"../data/audio/push_ice.mp3" };
	inline static const real::Sound push_wall = { 1, VOLUME, 0, -1,
	"../data/audio/push_wall.mp3" };
	inline static const real::Sound sno_bee_killed = { 1, VOLUME, 0, -1,
	"../data/audio/sno_bee_killed.mp3" };
	inline static const real::Sound sno_bee_spawned = { 1, VOLUME, 0, -1,
	"../data/audio/sno_bee_spawned.mp3" };
	inline static const real::Sound sno_bee_stunned = { 1, VOLUME, 0, -1,
	"../data/audio/sno_bee_stunned.mp3" };
	inline static const real::Sound time_bonus_extension = { 1, VOLUME, 0, -1,
	"../data/audio/time_bonus_extension.mp3" };
};

#endif // GAMEINFO_H