#ifndef GAMETIME_H
#define GAMETIME_H

#include "Singleton.h"

#include <chrono>

namespace dae
{
	class GameTime final : public Singleton<GameTime>
	{
	public:
		explicit GameTime() = default;
		virtual ~GameTime() override = default;

		GameTime(const GameTime& other) = delete;
		GameTime& operator=(const GameTime& rhs) = delete;
		GameTime(GameTime&& other) = delete;
		GameTime& operator=(GameTime&& rhs) = delete;

		virtual void Init() override;
		virtual void Update() override;

		float GetElapsed() const;
		float GetTotal() const;
		// TODO: use set precision or smthn
		UINT GetFPS() const { return m_FPS; };
		float GetfFPS() const { return m_fFPS; };

		[[nodiscard]] UINT StartTimer();
		float EndTimer(UINT id);

	private:
		std::chrono::steady_clock::time_point m_PrevTime{};
		float m_DeltaTime{};
		float m_TotalTime{};

		UINT m_FPS = 0;
		float m_fFPS = 0.0f;
		UINT m_FPSCount = 0;
		float m_FPSTimer = 0.0f;

		std::vector<std::chrono::steady_clock::time_point> m_Timers{};

	};
}

#endif // GAMETIME_H