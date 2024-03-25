#include "Level01.h"

#include "IcePrefab.h"
#include "LevelGenerator.h"
#include "LevelParser.h"
#include "Macros.h"

Level01::Level01(const dae::WindowSettings& settings)
	: Scene("level01", "gameplay")
	, m_Settings(settings)
{
}

void Level01::Load()
{
	LevelGenerator::GetInstance().GenerateLevel(this, m_Settings, 1);
	//LevelParser::ParseLevel(this, m_Settings, "../data/levels/level1-test.txt");
}
