#include "Maze.h"
#include <memory>
#include <iostream>

#include "PlayerPrefab.h"
#include "IcePrefab.h"
#include "StarBlockPrefab.h"
#include "HiddenEggPrefab.h"

#include "Macros.h"
#include "WallPrefab.h"

Maze::Maze(dae::GameObject* pOwner, const glm::ivec2& size)
	: Component(pOwner)
{
	m_Maze = std::vector(size.x, std::vector(size.y, BlockType::wall));
}

void Maze::Init() const
{
    const int mazeWidth = static_cast<int>(m_Maze.size());
    const int mazeHeight = static_cast<int>(m_Maze.front().size());

	// Add walls
		// Horizontal
	auto wall = std::make_unique<WallPrefab>(GetOwner(), glm::vec2{ WALL_WIDTH * PIXEL_SCALE, 0 }, true);
    wall = std::make_unique<WallPrefab>(GetOwner(), glm::vec2{ WALL_WIDTH * PIXEL_SCALE, mazeHeight * BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE }, true);
		// Vertical
    wall = std::make_unique<WallPrefab>(GetOwner(), glm::vec2{ 0, 0 }, false);
    wall = std::make_unique<WallPrefab>(GetOwner(), glm::vec2{ mazeWidth * BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE, 0 }, false);

    // Add Blocks
	for (size_t x = 0; x < m_Maze.size(); ++x)
    {
        for (size_t y = 0; y < m_Maze[x].size(); ++y)
        {
            //                                   Position                   Wall Offset
            auto scaledPos = glm::vec2(x * BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE, y * BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE);


            if (x == 6 && y == 6)
            {
                auto playerSpawn = std::make_unique<PlayerPrefab>(GetOwner(), scaledPos);
                std::cout << 'u';
            }

            switch (m_Maze[x][y])
            {
            case BlockType::wall:
            {
                auto ice = std::make_unique<IcePrefab>(GetOwner(), scaledPos);
                std::cout << "X";
                break;
            }
            case BlockType::star:
            {
                auto starBlock = std::make_unique<StarBlockPrefab>(GetOwner(), scaledPos);
                std::cout << "*";
                break;
            }
            case BlockType::egg:
            {
                auto hiddenEgg = std::make_unique<HiddenEggPrefab>(GetOwner(), scaledPos);
                std::cout << "!";
                break;
            }
            case BlockType::air:
            default:
                std::cout << '_';
            }
        }

        std::cout << '\n';
    }
}

void Maze::SetBlock(const glm::ivec2& pos, BlockType type)
{
	m_Maze[pos.x][pos.y] = type;
}

Maze::BlockType Maze::GetBlock(const glm::ivec2& pos) const
{
	return m_Maze[pos.x][pos.y];
}

bool Maze::IsOccupied(const glm::ivec2& pos) const
{
	return m_Maze[pos.x][pos.y] != BlockType::air;
}
