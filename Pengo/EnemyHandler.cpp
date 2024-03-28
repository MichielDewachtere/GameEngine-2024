#include "EnemyHandler.h"

#include <random>

#include <GameObject.h>

#include "Enemy.h"
#include "EnemyPrefab.h"
#include "Game.h"
#include "HiddenEgg.h"
#include "Move.h"

EnemyHandler::EnemyHandler(dae::GameObject* pOwner, int difficulty)
    : Component(pOwner)
{
    int spawns = 3;
    if (difficulty > 4)
        spawns = 4;

    m_AmountOfEnemiesAtOnce = spawns;
}

EnemyHandler::~EnemyHandler()
{
    GetOwner()->GetComponent<Game>()->gameStarted.RemoveObserver(this);
}

void EnemyHandler::Start()
{
    GetOwner()->GetComponent<Game>()->gameStarted.AddObserver(this);
}

void EnemyHandler::HandleEvent()
{
    if (m_EnemySpawns.empty())
        return;

    m_EnemySpawns.back()->PopEgg();
    SpawnSnoBee();
    m_EnemySpawns.pop_back();
}

void EnemyHandler::HandleEvent(GameEvents event)
{
    if (event == GameEvents::start)
    {
        for (int i{ 0 }; i < m_AmountOfEnemiesAtOnce; ++i)
        {
            m_EnemySpawns.back()->PopEgg();
            SpawnSnoBee();
            m_EnemySpawns.pop_back();
        }
    }
}

void EnemyHandler::AddEnemySpawn(dae::GameObject* go)
{
	m_EnemySpawns.push_back(go->GetComponent<HiddenEgg>());

    std::random_device rd;
    std::mt19937 g(rd());
    std::ranges::shuffle(m_EnemySpawns, g);
}

void EnemyHandler::RemoveEnemySpawn(dae::GameObject* go)
{
	const auto spawn = go->GetComponent<HiddenEgg>();
    std::erase(m_EnemySpawns, spawn);
}

void EnemyHandler::SpawnSnoBee()
{
	auto level = GetOwner();

	const auto spawn = m_EnemySpawns.back();
	auto mazePos = spawn->GetOwner()->GetParent()->GetComponent<Move>()->GetMazePos();
	auto pos = spawn->GetOwner()->GetParent()->GetTransform()->GetLocalPosition();

	const auto snoBee = std::make_unique<EnemyPrefab>(level, pos, mazePos);
    snoBee->GetGameObject()->GetComponent<Enemy>()->enemyDied.AddObserver(this);

    level->GetComponent<Maze>()->SetBlock(mazePos, Maze::BlockType::enemy, snoBee->GetGameObject());
}
