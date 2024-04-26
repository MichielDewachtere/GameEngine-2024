#include "LevelGenerator.h"

#include <chrono>
#include <random>
#include <ostream>

#include "Macros.h"
#include "Maze.h"
#include "Scene.h"

void LevelGenerator::GenerateLevel()
{
    constexpr int maxLevels = 16;

    for (int i{ 1 }; i <= maxLevels; ++i)
    {
        ResetMaze();
        // Start maze from the bottom left
        GenerateMaze(0, MAZE_HEIGHT - 1);
        GenerateSpecialBlocks(static_cast<uint8_t>(i));

        std::string fileName{ "level" };
        fileName += std::to_string(i);
        fileName += ".lvl";

        OutputMaze(fileName);
    }
}

// Recursive Backtracking Algorithm
void LevelGenerator::GenerateMaze(int x, int y)
{
    m_Maze[x][y] = air;

    constexpr int amountOfDirs = 4;
    constexpr int directionX[amountOfDirs] = { 1, 0, -1, 0 };
    constexpr int directionY[amountOfDirs] = { 0, 1, 0, -1 };

    // Shuffle directions
    std::vector<int> dirs = { 0, 1, 2, 3 };
    std::ranges::shuffle(dirs, m_Rand);

    for (const int dir : dirs)
    {
        // Move 2 steps in each direction to avoid "diagonals"
        int nx = x + 2 * directionX[dir];
        int ny = y + 2 * directionY[dir];
        if (IsValid(nx, ny))
        {
            //maze.SetBlock({ x + directionX[dir],y + directionY[dir] }, Maze::BlockType::air);
            m_Maze[x + directionX[dir]][y + directionY[dir]] = air;
            GenerateMaze(nx, ny);
        }
    }
}

void LevelGenerator::GenerateSpecialBlocks(uint8_t difficulty)
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
        for (int x = 1; x < MAZE_WIDTH - 1; ++x)
        {
            for (int y = 1; y < MAZE_HEIGHT - 1; ++y)
            {
                if (m_Maze[x][y] != wall)
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
                    constexpr int percentage = 2;
                    if (v == percentage)
                    {
                        ++amountOfStars;
                        //maze.SetBlock({ x,y }, Maze::BlockType::star);
                        m_Maze[x][y] = star;
                    }
                }
                else if (amountOfEggs < maxEggs)
                {
                    constexpr int percentage = 5;
                    if (v == percentage)
                    {
                        ++amountOfEggs;
                        //maze.SetBlock({ x,y }, Maze::BlockType::egg);
                        m_Maze[x][y] = egg;
                    }
                }
            }
        }
    }
}

void LevelGenerator::ResetMaze()
{
	m_Maze = std::vector(MAZE_WIDTH, std::vector(MAZE_HEIGHT, wall));
    m_Rand = std::mt19937(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));
}

bool LevelGenerator::IsValid(int x, int y) const
{
    return x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT && m_Maze[x][y] == wall;
    //return x >= 0 && x < m_Width && y >= 0 && y < m_Height && maze.GetBlock({ x,y }) == Maze::BlockType::ice;
}

void LevelGenerator::OutputMaze(std::string fileName) const
{
    // Create an ofstream object to write to a file
    std::ofstream outputFile;

    // Open the file. If the file doesn't exist, it will be created.
    const auto path = "../Data/Levels/" + std::move(fileName);
    outputFile.open(path);

    // Check if the file is successfully opened
    if (!outputFile.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
    }

    // Write to the file
    for (int y{ 0 }; y < static_cast<int>(m_Maze.front().size()); ++y)
    {
	    for (int x{ 0 }; x < static_cast<int>(m_Maze.size()); ++x)
	    {
            outputFile << m_Maze[x][y];
	    }

        outputFile << '\n';
    }

    // Close the file
    outputFile.close();

    real::Logger::LogInfo({ "Data has been written to {}" }, path);
}
