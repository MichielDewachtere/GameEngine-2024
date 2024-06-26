﻿#ifndef LEVELPARSER_H
#define LEVELPARSER_H

#include <string>

#include <Scene.h>

namespace real
{
	struct WindowSettings;
}

class LevelParser final
{
public:
	explicit LevelParser() = default;
	~LevelParser() = default;

	LevelParser(const LevelParser& other) = delete;
	LevelParser& operator=(const LevelParser& rhs) = delete;
	LevelParser(LevelParser&& other) = delete;
	LevelParser& operator=(LevelParser&& rhs) = delete;

	static void ParseLevel(real::Scene* pScene, const std::string& levelPath, int difficulty);

private:
	
};

#endif // LEVELPARSER_H