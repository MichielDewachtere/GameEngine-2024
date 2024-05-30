#ifndef GAME_H
#define GAME_H

#include <Subject.h>
#include <DrawableComponent.h>

enum class GameEvents : char
{
	started,
	paused,
	reset,
	resumed,
	finished,
};

class Game final : public real::DrawableComponent
{
public:
	explicit Game(real::GameObject* pOwner);
	virtual ~Game() override = default;

	Game(const Game& other) = delete;
	Game& operator=(const Game& rhs) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnGui() override;

	void EndAct(bool won);
	void EndGame();

	real::Subject<GameEvents> gameEvent;

	static float GetGameTime() { return m_GameTime; }
	static int GetCurrentLevel() { return m_CurrentLevel; }
	static void SetIsPvP(bool isPvP) { m_IsPvP = isPvP; }
	static int GetIsPvP() { return m_IsPvP; }

private:
	enum class GameState : char
	{
		start,
		running,
		paused,
		resume,
		actFinished,
		gameFinished
	};

	GameState m_CurrentState{ GameState::start };
	float m_StartTime{ 3.f }, m_AccuTime{ 0.f }, m_PauseTime{ 1.f };
	float m_CurtainTime{ 2.5f }, m_PauseCurtainTime{ 1.f };
	real::GameObject* m_pPauseText{ nullptr };

	void DrawCurtain(bool open, float curtainTime) const;

	static inline float m_GameTime{ 0.f };
	static inline int m_CurrentLevel{ 0 };
	static inline bool m_IsPvP{ false };
};

#endif // GAME_H