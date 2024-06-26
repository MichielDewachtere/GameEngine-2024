﻿#include "LevelParser.h"

#include <RealEngine.h>

#include "EnemyHandler.h"
#include "Game.h"
#include "GameInfo.h"
#include "Macros.h"
#include "Maze.h"
#include "PlayerManager.h"
#include "StarBlockManager.h"

void LevelParser::ParseLevel(real::Scene* pScene, const std::string& levelPath, int difficulty)
{
	std::ifstream file(levelPath);
	if (!file.is_open())
	{
		std::cerr << "Unable to open file: " << levelPath << '\n';
		return;
	}

	// Create Level Object
	auto& level = pScene->CreateGameObject({}, Tags::game);
	level.GetTransform()->SetLocalPosition({ 0, HUD_SIZE_TOP });
	if (Game::GetIsPvP() == false)
		level.AddComponent<EnemyHandler>(difficulty);

	const auto mazeComponent = level.AddComponent<Maze>(glm::ivec2{ MAZE_WIDTH, MAZE_HEIGHT});
	level.AddComponent<StarBlockManager>();
	level.AddComponent<Game>();

	PlayerManager::GetInstance().Reset();

	// Add Blocks
	std::string line;
	glm::vec2 pos{ 0, 0 };
	while (std::getline(file, line))
	{
		if (line[0] == '/'
			&& line[1] == '/'
			|| line.empty())
			continue;

		pos.x = 0;

		for (const char c : line)
		{
			// ReSharper disable once CppDefaultCaseNotHandledInSwitchStatement
			switch (c)  // NOLINT(hicpp-multiway-paths-covered)
			{
			case 'X':
			{
				mazeComponent->SetBlock(pos, Maze::BlockType::ice);
				break;
			}
			case '*':
			{
				mazeComponent->SetBlock(pos, Maze::BlockType::star);
				break;
			}
			case '!':
			{
				if (Game::GetIsPvP())
					mazeComponent->SetBlock(pos, Maze::BlockType::ice);
				else
					mazeComponent->SetBlock(pos, Maze::BlockType::egg);
				break;
			}
			}

			pos.x += 1;
		}

		pos.y += 1;
	}

	mazeComponent->Init();
}
