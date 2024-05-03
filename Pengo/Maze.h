#ifndef MAZE_H
#define MAZE_H

#include <glm/vec2.hpp>
#include <vector>
#include <map>

#include <Component.h>


enum class WallOrientation : char
{
	north = 0,
	east = 1,
	south = 2,
	west = 3,
	none = 4
};

class Maze final : public real::Component
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

	explicit Maze(real::GameObject* pOwner, const glm::ivec2& size);
	virtual ~Maze() override = default;

	Maze(const Maze& other) = delete;
	Maze& operator=(const Maze& rhs) = delete;
	Maze(Maze&& other) = delete;
	Maze& operator=(Maze&& rhs) = delete;

	// This function should only be called to initialize blocks!
	// Therefore it is best to only call it in the LevelGenerator class
	void Init();

	virtual void Start() override;

	void SetBlock(const glm::ivec2& pos, BlockType type, real::GameObject* go = nullptr);
	void RemoveBlock(const glm::ivec2& pos, real::GameObject* go);
	void MoveObject(const glm::ivec2& from, const glm::ivec2& to, BlockType type, real::GameObject* go = nullptr);

	BlockType GetBlock(const glm::ivec2& pos) const;
	std::vector<real::GameObject*> GetGameObject(const glm::ivec2& pos) const;
	std::pair<BlockType, std::vector<real::GameObject*>> GetBlockAndObject(const glm::ivec2& pos);

	real::GameObject* GetWall(WallOrientation orientation) const { return m_pWalls.at(orientation); }

	glm::ivec2 GetNearestFreePos(const glm::ivec2& pos) const;

	bool IsOccupied(const glm::ivec2& pos) const;
	static bool IsInBounds(const glm::ivec2& pos);
	void PrintMaze() const;

	static glm::ivec2 MazeToLocal(const glm::ivec2& pos);
	static glm::ivec2 LocalToMaze(const glm::ivec2& pos);

private:
	std::vector<std::vector<std::pair<BlockType, std::vector<real::GameObject*>>>> m_Maze{};
	std::map<WallOrientation, real::GameObject*> m_pWalls{};
	//			id			pos
	std::map<uint32_t, glm::ivec2> m_EnemyPositions;
	static std::pair<bool, WallOrientation> IsWall(const glm::ivec2& pos);

	static bool IsStatic(BlockType type);
	static bool IsDynamic(BlockType type);
};

#endif // MAZE_H
