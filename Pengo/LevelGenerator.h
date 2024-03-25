#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <Minigin.h>
#include <random>
#include <Singleton.h>

#include "Maze.h"

namespace dae
{
	class Scene;
}

class LevelGenerator final : public dae::Singleton<LevelGenerator>
{
public:
	void GenerateLevel(dae::Scene* pScene, dae::WindowSettings settings, uint8_t difficulty);

private:
	friend class Singleton<LevelGenerator>;
	LevelGenerator() = default;

	const uint8_t m_Width{ 13 }, m_Height{ 15 };
	std::mt19937 m_Rand;

	void GenerateMaze(Maze& maze, int x, int y);
	void GenerateSpecialBlocks(Maze& maze, uint8_t difficulty);
	void ResetMaze();
	bool IsValid(Maze& maze, int x, int y) const;
};

#endif // LEVELGENERATOR_H