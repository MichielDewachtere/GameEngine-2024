#include "Level.h"

#include "InputManager.h"
#include "LevelParser.h"

Level::Level(std::string level, std::string inputMap, bool debug)
	: Scene(std::move(level), std::move(inputMap))
	, m_Debug(debug)
{
}

void Level::Load()
{
	if (m_Debug)
	{
		LevelParser::ParseLevel(this, "../data/levels/debug.lvl", 5);
	}
	else
	{
		std::string levelPath = "../data/levels/";
		levelPath += GetName();
		levelPath += ".lvl";

		const int difficulty = stoi(GetName().substr(5));

		LevelParser::ParseLevel(this, levelPath, difficulty);
	}
}
