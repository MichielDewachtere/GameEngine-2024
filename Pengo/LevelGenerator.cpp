#include "LevelGenerator.h"

#include <chrono>
#include <random>

#include "Macros.h"
#include "Maze.h"
#include "Scene.h"

void LevelGenerator::GenerateLevel(dae::Scene* pScene, dae::WindowSettings /*settings*/, uint8_t difficulty)
{
    // Create Maze Object
    auto& maze = pScene->CreateGameObject();
    maze.GetTransform()->SetLocalPosition({ 0, 16 * PIXEL_SCALE });
    const auto mazeComponent = maze.AddComponent<Maze>(glm::ivec2{ m_Width, m_Height });

	ResetMaze();
    // Start maze from the bottom left
    GenerateMaze(*mazeComponent, 0, m_Height - 1);
    GenerateSpecialBlocks(*mazeComponent, difficulty);

    mazeComponent->Init();

    //glm::vec2 pos{ 0, 8 };

    //for (int y = 0; y < m_Height; ++y)
    //{
    //    pos.y += 16;
    //    pos.x = -8;

    //    for (int x = 0; x < m_Width; ++x)
    //    {
    //        pos.x += 16;
    //        auto scaledPos = glm::vec2(pos.x * PIXEL_SCALE, pos.y * PIXEL_SCALE);

    //        if (x == 6 && y == 6)
    //        {
    //            auto playerSpawn = std::make_unique<PlayerPrefab>(pScene, scaledPos);
    //            std::cout << 'u';
    //        }

    //        switch (m_Maze[y][x])
    //        {
    //        case BlockType::wall:
    //        {
    //            auto ice = std::make_unique<IcePrefab>(pScene, scaledPos);
    //            std::cout << "X";
    //            break;
    //        }
    //        case BlockType::star:
    //        {
    //            auto starBlock = std::make_unique<StarBlockPrefab>(pScene, scaledPos);
    //            std::cout << "*";
    //            break;
    //        }
    //        case BlockType::egg:
    //        {
    //            auto hiddenEgg = std::make_unique<HiddenEggPrefab>(pScene, scaledPos);
    //            std::cout << "!";
    //            break;
    //        }
    //        default:
    //            std::cout << '_';
    //        }
    //    }

    //    std::cout << '\n';
    //}

}

// Recursive Backtracking Algorithm
void LevelGenerator::GenerateMaze(Maze& maze, int x, int y)
{
    maze.SetBlock({ x,y }, Maze::BlockType::air);
    //m_Maze[y][x] == AIR;

    constexpr int amountOfDirs = 4;
    constexpr int directionX[amountOfDirs] = { 1, 0, -1, 0 };
    constexpr int directionY[amountOfDirs] = { 0, 1, 0, -1 };

    // Shuffle directions
    std::vector<int> dirs = { 0, 1, 2, 3 };
    std::shuffle(dirs.begin(), dirs.end(), m_Rand);

    for (int dir : dirs)
    {
        // Move 2 steps in each direction to avoid "diagonals"
        int nx = x + 2 * directionX[dir];
        int ny = y + 2 * directionY[dir];
        if (IsValid(maze, nx, ny))
        {
            maze.SetBlock({ x + directionX[dir],y + directionY[dir] }, Maze::BlockType::air);
            //m_Maze[y + directionY[dir]][x + directionX[dir]] = BlockType::air;
            GenerateMaze(maze, nx, ny);
        }
    }
}

void LevelGenerator::GenerateSpecialBlocks(Maze& maze, uint8_t difficulty)
{
    int amountOfStars = 0;
    int amountOfEggs = 0;

    constexpr int maxStars = 3;
    int maxEggs = 6; // Default value

    if (difficulty > 11)
    {
        maxEggs = 12;
    }
    else if (difficulty > 7)
    {
        maxEggs = 10;
    }
    else if (difficulty > 2)
    {
        maxEggs = 8;
    }


    constexpr int spawnRadius = 2, spawnBlock = 6;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 99);

    while (amountOfStars < maxStars || amountOfEggs < maxEggs)
    {
        for (int y = 1; y < m_Height - 1; ++y)
        {
            for (int x = 1; x < m_Width - 1; ++x)
            {
                if (maze.GetBlock({x,y})!= Maze::BlockType::wall)
                    continue;

				//disable spawns of sno-bee for distance of 2
                if (y >= spawnBlock - spawnRadius 
                    && y <= spawnBlock + spawnRadius
					&& x >= spawnBlock - spawnRadius 
                    && x <= spawnBlock + spawnRadius)
                {
	                continue;
                }

                int v = dist(gen);

                if (amountOfStars < maxStars)
                {
                    constexpr int perc = 2;
                    if (v == perc)
                    {
                        ++amountOfStars;
                        maze.SetBlock({ x,y }, Maze::BlockType::star);
                        //m_Maze[y][x] = BlockType::star;
                    }
                }
                else if (amountOfEggs < maxEggs)
                {
                    constexpr int perc = 5;
                    if (v == perc)
                    {
                        ++amountOfEggs;
                        maze.SetBlock({ x,y }, Maze::BlockType::egg);
                        //m_Maze[y][x] = BlockType::egg;
                    }
                }
            }
        }
    }
}

void LevelGenerator::ResetMaze()
{
	//m_Maze = std::vector(m_Height, std::vector(m_Width, BlockType::wall));
    m_Rand = std::mt19937(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));
}

bool LevelGenerator::IsValid(Maze& maze, int x, int y) const
{
    //return x >= 0 && x < m_Width && y >= 0 && y < m_Height && m_Maze[y][x] == BlockType::wall;
    return x >= 0 && x < m_Width && y >= 0 && y < m_Height && maze.GetBlock({ x,y }) == Maze::BlockType::wall;
}
