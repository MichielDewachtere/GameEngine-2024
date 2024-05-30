#ifndef ENEMYPLAYER_H
#define ENEMYPLAYER_H

#include <memory>

#include "Enemy.h"
#include "Game.h"
#include "IEnemyState.h"
#include "Player.h"

class EnemyPlayer final
	: public Player
	, public real::Observer<GameEvents>
	, public real::Observer<WallOrientation>
{
public:
	explicit EnemyPlayer(real::GameObject* pOwner, PlayerNumber number);
	virtual ~EnemyPlayer() override;

	EnemyPlayer(const EnemyPlayer& other) = delete;
	EnemyPlayer& operator=(const EnemyPlayer& rhs) = delete;
	EnemyPlayer(EnemyPlayer&& other) = delete;
	EnemyPlayer& operator=(EnemyPlayer&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	virtual void HandleEvent(GameEvents) override;
	virtual void HandleEvent(WallOrientation) override;
	virtual void OnSubjectDestroy() override {}

	void Push(Direction direction);

private:
	std::unique_ptr<IEnemyState> m_pCurrentState;
};

#endif // ENEMYPLAYER_H
