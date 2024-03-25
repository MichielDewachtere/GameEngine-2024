#include "LevelParser.h"

#include <Minigin.h>

#include "HiddenEggPrefab.h"
#include "IcePrefab.h"
#include "Macros.h"
#include "StarBlockPrefab.h"
#include "WallPrefab.h"

void LevelParser::ParseLevel(dae::Scene* pScene, dae::WindowSettings settings, std::string levelPath)
{
	std::ifstream file(levelPath);
	if (!file.is_open())
	{
		std::cerr << "Unable to open file: " << levelPath << '\n';
		return;
	}

	// Add walls
	auto wall = std::make_unique<WallPrefab>(pScene, glm::vec2{ 8 * PIXEL_SCALE,16 * PIXEL_SCALE }, true);
	wall = std::make_unique<WallPrefab>(pScene, glm::vec2{ 8 * PIXEL_SCALE, settings.height - 8 * PIXEL_SCALE}, true);
	wall = std::make_unique<WallPrefab>(pScene, glm::vec2{ 0,16 * PIXEL_SCALE }, false);
	wall = std::make_unique<WallPrefab>(pScene, glm::vec2{ settings.width - 8 * PIXEL_SCALE, 16 * PIXEL_SCALE }, false);


	int counter = 0;

	// Add Blocks
	std::string line;
	glm::vec2 pos{ 0, 8 };
	while (std::getline(file, line))
	{
		if (line[0] == '/' 
			&& line[1] == '/'
			|| line.empty())
			continue;

		pos.y += 16;
		pos.x = -8;

		for (char c : line)
		{

			pos.x += 16;

			auto scaledPos = glm::vec2(pos.x * PIXEL_SCALE, pos.y * PIXEL_SCALE);

			switch (c)
			{
			case 'X':
			{
				++counter;
				auto ice = std::make_unique<IcePrefab>(pScene, scaledPos);
				std::cout << "X";
				break;
			}
			case '*':
			{
				auto starBlock = std::make_unique<StarBlockPrefab>(pScene, scaledPos);
				std::cout << "*";
				break;
			}
			case '!':
			{
				auto hiddenEgg = std::make_unique<HiddenEggPrefab>(pScene, scaledPos);
				std::cout << "!";
				break;
			}
			case 'O':
			{
				std::cout << "O";
				break;
			}
			case 'u':
			{
				std::cout << "u";
				break;
			}
			default: 
				std::cout << '_';
			}
		}
		std::cout << '\n';
	}

	std::cout << counter << '\n';
}
