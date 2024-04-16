﻿#include "EnemyHandler.h"

#include <random>

#include <GameObject.h>

#include "Enemy.h"
#include "EnemyPrefab.h"
#include "Game.h"
#include "GameInfo.h"
#include "HiddenEgg.h"
#include "Move.h"
#include "Pushable.h"

EnemyHandler::EnemyHandler(real::GameObject* pOwner, int difficulty)
    : Component(pOwner)
{
    int spawns = 3;
    if (difficulty > 4)
        spawns = 4;

    m_AmountOfEnemiesAtOnce = spawns;
}

EnemyHandler::~EnemyHandler()
{
    m_pGameComponent->gameEvent.RemoveObserver(this);
}

void EnemyHandler::Start()
{
    m_pGameComponent = GetOwner()->GetComponent<Game>();
    m_pGameComponent->gameEvent.AddObserver(this);
}

void EnemyHandler::Update()
{
    if (m_PushedEgg && m_PushedEgg->IsBeingPushed() == false)
    {
        m_EnemySpawns.back()->PopEgg();
        SpawnSnoBee();
        m_EnemySpawns.pop_back();

        m_PushedEgg = nullptr;
    }
}

void EnemyHandler::Kill()
{
    auto v = GetOwner()->GetGameObjectsWithTag(Tags::sno_bee);
    if (v.empty() == false)
    {
        std::ranges::for_each(v, [this](real::GameObject* go)
            {
                go->GetComponent<Enemy>()->enemyDied.RemoveObserver(this);
            });
    }
}

void EnemyHandler::HandleEvent()
{
    --m_TotalEnemies;

    if (m_EnemySpawns.empty())
    {
        if (m_TotalEnemies == 0)
            m_pGameComponent->EndAct(true);

        return;
    }

    const auto iceBlock = m_EnemySpawns.back()->GetOwner()->GetParent()->GetComponent<Pushable>();
    if (iceBlock->IsBeingPushed())
    {
        m_PushedEgg = iceBlock;
        return;
    }

    m_EnemySpawns.back()->PopEgg();
    SpawnSnoBee();
    m_EnemySpawns.pop_back();
}

void EnemyHandler::HandleEvent(GameEvents event)
{
    if (event == GameEvents::started)
    {
        for (int i{ 0 }; i < m_AmountOfEnemiesAtOnce; ++i)
        {
            m_EnemySpawns.back()->PopEgg();
            SpawnSnoBee();
            m_EnemySpawns.pop_back();
        }
    }
}

void EnemyHandler::AddEnemySpawn(real::GameObject* go)
{
	m_EnemySpawns.push_back(go->GetComponent<HiddenEgg>());

    std::random_device rd;
    std::mt19937 g(rd());
    std::ranges::shuffle(m_EnemySpawns, g);

    ++m_TotalEnemies;
}

void EnemyHandler::RemoveEnemySpawn(real::GameObject* go)
{
	const auto spawn = go->GetComponent<HiddenEgg>();
    std::erase(m_EnemySpawns, spawn);

    std::cout << "+500\n";

	--m_TotalEnemies;
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
