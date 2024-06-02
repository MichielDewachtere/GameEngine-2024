#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <Component.h>
#include <vector>
#include <Observer.h>
#include <Subject.h>

class Pushable;
class Game;
enum class GameEvents : char;
class HiddenEgg;

class EnemyHandler final
	: public real::Component
	, public real::Observer<>
	, public real::Observer<GameEvents>
{
public:
	explicit EnemyHandler(real::GameObject* pOwner, int difficulty);
	virtual ~EnemyHandler() override;

	EnemyHandler(const EnemyHandler& other) = delete;
	EnemyHandler& operator=(const EnemyHandler& rhs) = delete;
	EnemyHandler(EnemyHandler&& other) = delete;
	EnemyHandler& operator=(EnemyHandler&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;
	virtual void Kill() override;

	virtual void HandleEvent() override;
	virtual void HandleEvent(GameEvents) override;
	virtual void OnSubjectDestroy() override {}

	void AddEnemySpawn(real::GameObject* go);
	void RemoveEnemySpawn(real::GameObject* go);

	static int GetAmountOfEnemies() { return m_TotalEnemies; }

	real::Subject<> enemySpawned;

private:
	int m_AmountOfEnemiesAtOnce{};
	std::vector<HiddenEgg*> m_EnemySpawns;
	Game* m_pGameComponent{ nullptr };
	Pushable* m_PushedEgg{ nullptr };

	static inline int m_TotalEnemies{};

	void SpawnSnoBee();
	static float CalculateSpeed();
};

#endif // ENEMYHANDLER_H