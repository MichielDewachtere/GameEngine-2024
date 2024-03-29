#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <Component.h>
#include <vector>
#include <Observer.h>

class Game;
enum class GameEvents : char;
class HiddenEgg;

enum class EnemyKillEvent
{
	singleKill,
	doubleKill,
	tripleKill,
	quadKill,
	eggKill,
	stunKill
};

class EnemyHandler final
	: public dae::Component
	, public dae::Observer<>
	, public dae::Observer<GameEvents>
{
public:
	explicit EnemyHandler(dae::GameObject* pOwner, int difficulty);
	virtual ~EnemyHandler() override;

	EnemyHandler(const EnemyHandler& other) = delete;
	EnemyHandler& operator=(const EnemyHandler& rhs) = delete;
	EnemyHandler(EnemyHandler&& other) = delete;
	EnemyHandler& operator=(EnemyHandler&& rhs) = delete;

	virtual void Start() override;
	virtual void Kill() override;

	virtual void HandleEvent() override;
	virtual void HandleEvent(GameEvents) override;
	virtual void OnSubjectDestroy() override {}

	void AddEnemySpawn(dae::GameObject* go);
	void RemoveEnemySpawn(dae::GameObject* go);

private:
	int m_AmountOfEnemiesAtOnce{}, m_TotalEnemies{};
	std::vector<HiddenEgg*> m_EnemySpawns;
	Game* m_pGameComponent{ nullptr };

	void SpawnSnoBee();
};

#endif // ENEMYHANDLER_H