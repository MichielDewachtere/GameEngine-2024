#ifndef GAMEUTIL_H
#define GAMEUTIL_H

#include <glm/vec2.hpp>

#include "Move.h"

inline glm::ivec2 DirectionToVector(Direction dir)
{
	switch (dir)
	{
	case Direction::up:
		return { 0,-1 };
	case Direction::right:
		return { 1,0 };
	case Direction::left:
		return { -1,0 };
	case Direction::down:
		return { 0,1 };
	default:
		return { 0,0 };
	}
}

inline Direction InvertDirection(Direction dir)
{
	switch (dir)
	{
	case Direction::up:
		return Direction::down;
	case Direction::right:
		return Direction::left;
	case Direction::left:
		return Direction::right;
	case Direction::down:
		return Direction::up;
	default:
		return dir;
	}
}

#endif // GAMEUTIL_H