#ifndef ENEMYHANDLER_H
#define ENEMYHANDLER_H

#include <Component.h>
#include <vector>
#include <Observer.h>

class HiddenEgg;

class EnemyHandler final
	: public dae::Component
	, public dae::Observer<>
{
public:
	explicit EnemyHandler(dae::GameObject* pOwner, int difficulty);
	virtual ~EnemyHandler() override = default;

	EnemyHandler(const EnemyHandler& other) = delete;
	EnemyHandler& operator=(const EnemyHandler& rhs) = delete;
	EnemyHandler(EnemyHandler&& other) = delete;
	EnemyHandler& operator=(EnemyHandler&& rhs) = delete;

	virtual void Start() override;

	virtual void HandleEvent() override;
	virtual void OnSubjectDestroy() override {}

	void AddEnemySpawn(dae::GameObject* go);
	void RemoveEnemySpawn(dae::GameObject* go);

private:
	int m_AmountOfEnemiesAtOnce{};
	std::vector<HiddenEgg*> m_EnemySpawns;

	void SpawnSnoBee();
};

#endif // ENEMYHANDLER_H