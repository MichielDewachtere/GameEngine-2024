#ifndef MAZE_H
#define MAZE_H

#include <glm/vec2.hpp>

#include <Component.h>
#include <vector>

class Maze final : public dae::Component
{
public:
	enum class BlockType : char
	{
		air = 0,
		wall = 1,
		star = 2,
		egg = 3,
	};

	explicit Maze(dae::GameObject* pOwner, const glm::ivec2& size);
	virtual ~Maze() override = default;

	Maze(const Maze& other) = delete;
	Maze& operator=(const Maze& rhs) = delete;
	Maze(Maze&& other) = delete;
	Maze& operator=(Maze&& rhs) = delete;

	// This function should only be called to initialize blocks!
	// Therefore it is best to only call it in the LevelGenerator class
	void Init() const;

	void SetBlock(const glm::ivec2& pos, BlockType type);
	BlockType GetBlock(const glm::ivec2& pos) const;
	bool IsOccupied(const glm::ivec2& pos) const;

private:
	// TODO: Stores entire maze, is owner of every object inside the maze
	// Use this instead of collider components?
	// TODO: store game objects too? Easy way of getting blocks?
	std::vector<std::vector<BlockType>> m_Maze{};
};

#endif // MAZE_H