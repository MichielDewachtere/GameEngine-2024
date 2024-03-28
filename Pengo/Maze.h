#ifndef MAZE_H
#define MAZE_H

#include <glm/vec2.hpp>
#include <vector>
#include <map>

#include <Component.h>

class Maze final : public dae::Component
{
public:
	enum class BlockType : char
	{
		air = 0,
		ice = 1,
		star = 2,
		egg = 3,
		wall = 4,
		player = 5,
		enemy = 6,
		none = 7
	};

	enum class WallOrientation : char
	{
		north = 0,
		east = 1,
		south = 2,
		west = 3,
		none = 4
	};

	explicit Maze(dae::GameObject* pOwner, const glm::ivec2& size);
	virtual ~Maze() override = default;

	Maze(const Maze& other) = delete;
	Maze& operator=(const Maze& rhs) = delete;
	Maze(Maze&& other) = delete;
	Maze& operator=(Maze&& rhs) = delete;

	// This function should only be called to initialize blocks!
	// Therefore it is best to only call it in the LevelGenerator class
	void Init();

	void SetBlock(const glm::ivec2& pos, BlockType type, dae::GameObject* go = nullptr);

	BlockType GetBlock(const glm::ivec2& pos) const;
	dae::GameObject* GetGameObject(const glm::ivec2& pos) const;
	std::pair<BlockType, dae::GameObject*> GetBlockAndObject(const glm::ivec2& pos);

	dae::GameObject* GetWall(WallOrientation orientation) const { return m_pWalls.at(orientation); }

	bool IsOccupied(const glm::ivec2& pos) const;

	static glm::ivec2 MazeToLocal(const glm::ivec2& pos);
	static glm::ivec2 LocalToMaze(const glm::ivec2& pos);

private:
	std::vector<std::vector<std::pair<BlockType, dae::GameObject*>>> m_Maze{};
	std::map<WallOrientation, dae::GameObject*> m_pWalls{};

	static std::pair<bool, WallOrientation> IsWall(const glm::ivec2& pos);
};

#endif // MAZE_H
