#include "Maze.h"

#include <memory>

#include <GameObject.h>
#include <InputManager.h>

#include "EnemyHandler.h"
#include "GameInfo.h"
#include "HiddenEggPrefab.h"
#include "PlayerPrefab.h"
#include "IcePrefab.h"
#include "StarBlockPrefab.h"

#include "Macros.h"
#include "Player.h"
#include "PlayerEnemyPrefab.h"
#include "PlayerManager.h"
#include "PrintMazeCommand.h"
#include "StarBlockManager.h"
#include "WallPrefab.h"

Maze::Maze(real::GameObject* pOwner, const glm::ivec2& size)
	: Component(pOwner)
{
    m_Maze = std::vector(
	    size.x, std::vector<std::pair<BlockType, std::vector<real::GameObject*>>>(
		    size.y, std::make_pair(BlockType::air, std::vector<real::GameObject*>{})));
}

void Maze::Init()
{
    const int mazeWidth = static_cast<int>(m_Maze.size());
    const int mazeHeight = static_cast<int>(m_Maze.front().size());

    {
        // Add walls
            // Horizontal
        auto wall = std::make_unique<WallPrefab>(GetOwner(), glm::vec2{WALL_WIDTH * PIXEL_SCALE, 0}, true,
                                                 WallOrientation::north);
        m_pWalls[WallOrientation::north] = wall->GetGameObject();
        wall = std::make_unique<WallPrefab>(GetOwner(), glm::vec2{
	                                            WALL_WIDTH * PIXEL_SCALE,
	                                            mazeHeight * BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE
                                            }, true, WallOrientation::south);
        m_pWalls[WallOrientation::south] = wall->GetGameObject();
        // Vertical
        wall = std::make_unique<WallPrefab>(GetOwner(), glm::vec2{0, 0}, false,
                                            WallOrientation::west);
        m_pWalls[WallOrientation::west] = wall->GetGameObject();
        wall = std::make_unique<WallPrefab>(
	        GetOwner(), glm::vec2{mazeWidth * BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE, 0}, false,
	        WallOrientation::east);
        m_pWalls[WallOrientation::east] = wall->GetGameObject();
    }


    // Add Blocks
    for (size_t x = 0; x < m_Maze.size(); ++x)
    {
        for (size_t y = 0; y < m_Maze[x].size(); ++y)
        {
            //                                   Position              |     Wall Offset
            auto scaledPos = glm::vec2(x * BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE, y * BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE);

            if (PlayerManager::GetInstance().RequestPlayer())
            {
                if (x == 6 && y == 6)
                {
                    const auto player = std::make_unique<PlayerPrefab>(GetOwner(), scaledPos, glm::ivec2{ x,y }, PlayerNumber::playerOne);
                    PlayerManager::GetInstance().SetObjectAndPosition(1, player->GetGameObject(), glm::ivec2{ x,y });
                }
                if (x == 6 && y == 10)
                {
                    if (PlayerManager::GetInstance().GetPlayers().back().isEnemy)
                    {
	                    const auto player = std::make_unique<PlayerEnemyPrefab>(GetOwner(), scaledPos, glm::ivec2{ x,y }, PlayerNumber::playerTwo);
                		PlayerManager::GetInstance().SetObjectAndPosition(2, player->GetGameObject(), glm::ivec2{ x,y });
                    }
                    else
                    {
	                    const auto player = std::make_unique<PlayerPrefab>(GetOwner(), scaledPos, glm::ivec2{ x,y }, PlayerNumber::playerTwo);
                		PlayerManager::GetInstance().SetObjectAndPosition(2, player->GetGameObject(), glm::ivec2{ x,y });
                    }
                }
            }

            switch (m_Maze[x][y].first)
            {
            case BlockType::ice:
            {
                const auto ice = std::make_unique<IcePrefab>(GetOwner(), scaledPos, glm::ivec2{ x,y });
                //m_Maze[x][y].second.push_back(ice->GetGameObject());
                break;
            }
            case BlockType::star:
            {
                const auto starBlock = std::make_unique<StarBlockPrefab>(GetOwner(), scaledPos, glm::ivec2{ x,y });
                GetOwner()->GetComponent<StarBlockManager>()->AddStarBlock(starBlock->GetGameObject(), glm::ivec2{ x,y });
                //m_Maze[x][y].second.push_back(starBlock->GetGameObject());
                break;
            }
            case BlockType::egg:
            {
                const auto iceBlock = std::make_unique<IcePrefab>(GetOwner(), scaledPos, glm::ivec2{ x,y }, true);
                const auto hiddenEgg = std::make_unique<HiddenEggPrefab>(iceBlock->GetGameObject());
                GetOwner()->GetComponent<EnemyHandler>()->AddEnemySpawn(hiddenEgg->GetGameObject());
                //m_Maze[x][y].second.push_back(iceBlock->GetGameObject());
                break;
            }
            }
        }
    }
}

void Maze::Start()
{
#ifdef _DEBUG
    const auto map = real::InputManager::GetInstance().GetActiveInputMap();
    map->AddKeyboardAction<PrintMazeCommand>(InputCommands::print_maze, real::KeyState::keyDown, SDL_SCANCODE_F5, GetOwner());
#endif
}

void Maze::SetBlock(const glm::ivec2& pos, BlockType type, real::GameObject* go)
{
    if (const auto [isWall, orientation] = IsWall(pos); isWall)
    {
        return;
    }

    m_Maze[pos.x][pos.y].first = type;
    m_Maze[pos.x][pos.y].second.clear();
    m_Maze[pos.x][pos.y].second.push_back(go);
}

void Maze::RemoveBlock(const glm::ivec2& pos, real::GameObject* go)
{
    using v = std::vector<real::GameObject*>;
    v& gameObjects = m_Maze[pos.x][pos.y].second;

    const auto it = std::ranges::find(gameObjects, go);
    if (it == gameObjects.end())
        return;

    gameObjects.erase(it);

    if (gameObjects.empty())
        m_Maze[pos.x][pos.y].first = BlockType::air;
}

void Maze::MoveObject(const glm::ivec2& from, const glm::ivec2& to, BlockType type, real::GameObject* go)
{
    if (const auto [isWall, orientation] = IsWall(to); isWall)
    {
        return;
    }

    //auto [fromBlockType, fromObjects] = m_Maze[from.x][from.y];
    auto [toBlockType, toObjects] = m_Maze[to.x][to.y];

 //   // TODO: Fix this for enemy crushing
 //   if ((type != BlockType::enemy && type != BlockType::player) 
 //       && toBlockType != type/* && toBlockType != BlockType::air*/)
	//{
	//	if (toBlockType != type)
	//	{
	//		//m_Maze[to.x][to.y].first = type;
	//		m_Maze[to.x][to.y].second.clear();
	//		//m_Maze[to.x][to.y].second.push_back(go);
	//	}
	//}

    //if (toBlockType != type && toBlockType != BlockType::ice && type != BlockType::enemy)
    //{
    //    m_Maze[to.x][to.y].second.clear();
    //}
    //else if (toBlockType != type && toBlockType == BlockType::enemy && type == BlockType::ice)
    //{
    //    m_Maze[to.x][to.y].second.clear();
    //}

    const auto it = std::ranges::find(m_Maze[from.x][from.y].second, go);
    if (it != m_Maze[from.x][from.y].second.end())
    {
		m_Maze[from.x][from.y].second.erase(it);
        //return;
    }

    if (toBlockType == type || IsDynamic(toBlockType) || IsStatic(type))
    	m_Maze[to.x][to.y].first = type;

    if (toBlockType == BlockType::air)
    	m_Maze[to.x][to.y].first = type;

    m_Maze[to.x][to.y].second.push_back(go);

    if (m_Maze[from.x][from.y].second.empty())
        m_Maze[from.x][from.y].first = BlockType::air;
}

Maze::BlockType Maze::GetBlock(const glm::ivec2& pos) const
{
    if (const auto [isWall, orientation] = IsWall(pos); isWall)
    {
        return BlockType::wall;
    }

	return m_Maze[pos.x][pos.y].first;
}

std::vector<real::GameObject*> Maze::GetGameObject(const glm::ivec2& pos) const
{
    if (const auto [isWall, orientation] = IsWall(pos); isWall)
    {
        return { m_pWalls.at(orientation) };
    }

	return m_Maze[pos.x][pos.y].second;
}

std::pair<Maze::BlockType, std::vector<real::GameObject*>> Maze::GetBlockAndObject(const glm::ivec2& pos)
{
    if (const auto [isWall, orientation] = IsWall(pos); isWall)
    {
        return { BlockType::wall, {m_pWalls.at(orientation) } };
    }

    return m_Maze[pos.x][pos.y];
}

glm::ivec2 Maze::GetNearestFreePos(const glm::ivec2& pos) const
{
    if (m_Maze[pos.x][pos.y].first == BlockType::air)
        return pos;

    glm::ivec2 dir[]{
        { 1, 0},{ 1, 1},{ 0, 1},{-1, 1},
        {-1, 0},{-1,-1},{ 0,-1},{ 1,-1}
    };

    int counter = 1;
    while (counter < 3)
    {
	    for (const auto & d : dir)
	    {
		    const auto posToCheck = pos + (d * counter);
            if (IsInBounds(posToCheck) == false)
                continue;

            if (m_Maze[posToCheck.x][posToCheck.y].first == BlockType::air)
            {
	            return posToCheck;
            }
	    }

        ++counter;
    }

    return {};
}

bool Maze::IsOccupied(const glm::ivec2& pos) const
{
    if (const auto [isWall, orientation] = IsWall(pos); isWall)
    {
        return true;
    }

    const auto type = m_Maze[pos.x][pos.y].first;
    using enum BlockType;
    return !(type == air || type == player || type == enemy);
}

bool Maze::IsInBounds(const glm::ivec2& pos)
{
    return pos.x >= 0 && pos.x < MAZE_WIDTH && pos.y >= 0 && pos.y < MAZE_HEIGHT;
}

void Maze::PrintMaze() const
{
    std::cout << "+-=-=-=-=-=-=-+\n";
    std::cout << "| MAZE LAYOUT |\n";
    std::cout << "+-=-=-=-=-=-=-+\n";
	for (int y{ 0 }; y < MAZE_HEIGHT; ++y)
    {
        std::cout << '|';

		for (int x{0}; x < MAZE_WIDTH; ++x)
        {
            switch (m_Maze.at(x).at(y).first)
            {
            case BlockType::air:
                std::cout << '_';
                break;
            case BlockType::ice:
                std::cout << 'X';
                break;
            case BlockType::star:
                std::cout << '*';
                break;
            case BlockType::egg:
                std::cout << '!';
                break;
            case BlockType::wall:
                std::cout << '.';
                break;
            case BlockType::player:
                std::cout << 'u';
                break;
            case BlockType::enemy:
            {
                auto v = m_Maze.at(x).at(y).second;
	            std::cout << std::to_string(v.size()).c_str();
                break;
            }
            case BlockType::none:
                std::cout << '_';
                break;
            }
        }

        std::cout << "|\n";
    }
    std::cout << "+-=-=-=-=-=-=-+\n\n";
}

glm::ivec2 Maze::MazeToLocal(const glm::ivec2& pos)
{
    return {
	    pos.x * BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE,
	    pos.y * BLOCK_SIZE * PIXEL_SCALE + WALL_WIDTH * PIXEL_SCALE
    };
}

glm::ivec2 Maze::LocalToMaze(const glm::ivec2& localPos)
{
    return {
        (localPos.x - WALL_WIDTH * PIXEL_SCALE) / (BLOCK_SIZE * PIXEL_SCALE),
        (localPos.y - WALL_WIDTH * PIXEL_SCALE) / (BLOCK_SIZE * PIXEL_SCALE)
    };
}

std::pair<bool, WallOrientation> Maze::IsWall(const glm::ivec2& pos)
{
    if (pos.x < 0)
        return { true, WallOrientation::west };

    if (pos.x >= MAZE_WIDTH)
        return { true, WallOrientation::east };

    if (pos.y < 0)
        return { true, WallOrientation::south };

    if (pos.y >= MAZE_HEIGHT)
        return { true, WallOrientation::north };

    return { false, WallOrientation::none };
}

bool Maze::IsStatic(BlockType type)
{
    return type == BlockType::egg
        || type == BlockType::ice
        || type == BlockType::star;
}

bool Maze::IsDynamic(BlockType type)
{
    return type == BlockType::enemy
        || type == BlockType::player;
}
