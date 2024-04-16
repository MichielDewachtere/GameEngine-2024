#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <RealEngine.h>
#include <random>
#include <Singleton.h>

namespace real
{
	class Scene;
}

class LevelGenerator final : public real::Singleton<LevelGenerator>
{
public:
	void GenerateLevel();

private:
	friend class Singleton<LevelGenerator>;
	LevelGenerator() = default;

	std::vector<std::vector<char>> m_Maze;
	std::mt19937 m_Rand;

	static constexpr char air{ '_' }, wall{ 'X' }, star{ '*' }, egg{ '!' };

	void GenerateMaze(int x, int y);
	void GenerateSpecialBlocks(uint8_t difficulty);
	void ResetMaze();
	bool IsValid(int x, int y) const;

	void OutputMaze(std::string fileName) const;
};

#endif // LEVELGENERATOR_H