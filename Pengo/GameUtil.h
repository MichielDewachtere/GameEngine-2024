// ReSharper disable CppIncompleteSwitchStatement
// ReSharper disable CppDefaultCaseNotHandledInSwitchStatement
#ifndef GAMEUTIL_H
#define GAMEUTIL_H

#include <glm/vec2.hpp>

#include "Move.h"
#include "PlayerManager.h"

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

inline glm::u8vec4 GetColorFromEnum(ECharacterColors color)
{
	switch (color)
	{
	case ECharacterColors::blue:
		return { 0,0,255,255 };
	case ECharacterColors::cyan: 
		return { 0,222,255,255 };
	case ECharacterColors::gold: 
		return { 222,222,0,255 };
	case ECharacterColors::green: 
		return { 0,255,0,255 };
	case ECharacterColors::lightYellow:
		return { 255,255,81,255 };
	case ECharacterColors::orange: 
		return { 255,184,0,255 };
	case ECharacterColors::pink: 
		return { 255,184,255,255 };
	case ECharacterColors::red: 
		return { 255,0,0,255 };
	case ECharacterColors::yellow: 
		return { 255,255,0,255 };
	}

	return { 255,255,255,255 };
}

inline std::string GetFileExtensionFromColor(ECharacterColors color)
{
	switch (color)
	{
	case ECharacterColors::blue:
		return "_blue.png";
	case ECharacterColors::cyan: 
		return "_cyan.png";
	case ECharacterColors::gold: 
		return "_gold.png";
	case ECharacterColors::green: 
		return "_green.png";
	case ECharacterColors::lightYellow:
		return "_light_yellow.png";
	case ECharacterColors::orange: 
		return "_orange.png";
	case ECharacterColors::pink: 
		return "_pink.png";
	case ECharacterColors::red: 
		return "_red.png";
	case ECharacterColors::yellow: 
		return "_yellow.png";
	}

	return "_green.png";
}

inline std::string GetNameFromColor(ECharacterColors color)
{
	switch (color)
	{
	case ECharacterColors::blue:
		return "blue";
	case ECharacterColors::cyan: 
		return "cyan";
	case ECharacterColors::gold: 
		return "gold";
	case ECharacterColors::green: 
		return "green";
	case ECharacterColors::lightYellow:
		return "light yellow";
	case ECharacterColors::orange: 
		return "orange";
	case ECharacterColors::pink: 
		return "pink";
	case ECharacterColors::red: 
		return "red";
	case ECharacterColors::yellow: 
		return "yellow";
	}

	return "green";
}

inline int GetSpriteIndexFromColor(ECharacterColors color)
{
	switch (color)
	{
	case ECharacterColors::blue:
		return 7;
	case ECharacterColors::cyan:
		return 7;
	case ECharacterColors::gold:
		return 8;
	case ECharacterColors::green:
		return 1;
	case ECharacterColors::lightYellow:
		return 6;
	case ECharacterColors::orange:
		return 5;
	case ECharacterColors::pink:
		return 4;
	case ECharacterColors::red:
		return 2;
	case ECharacterColors::yellow:
		return 3;
	}

	return 0;

}

#endif // GAMEUTIL_H