#ifndef GAME_H
#define GAME_H

#include <Subject.h>
#include <DrawableComponent.h>

enum class GameEvents : bool
{
	start,
	stop
};

class Game final : public dae::DrawableComponent
{
public:
	explicit Game(dae::GameObject* pOwner);
	virtual ~Game() override = default;

	Game(const Game& other) = delete;
	Game& operator=(const Game& rhs) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& rhs) = delete;

	virtual void Update() override;
	virtual void Render() override;

	void EndGame();

	dae::Subject<GameEvents> gameStarted;

private:
	bool m_GameFinished{ false }, m_GameStarted{ false };
	float m_StartTime{ 5.f }, m_AccuTime{ 0.f }, m_GameTime{ 0.f }, m_CurtainTime{ 4.5f };

	void DrawCurtain() const;
};

#endif // GAME_H