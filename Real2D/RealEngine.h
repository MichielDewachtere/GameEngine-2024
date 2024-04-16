#ifndef MINIGIN_H
#define MINIGIN_H

#include <functional>
#include <stdint.h>
#include <string>

namespace real
{
	struct WindowSettings
	{
		uint32_t width = 640, height = 480, fps = 60;
		float frameTime = 0.016f;
		std::string windowTitle, dataPath;
	};

	class RealEngine
	{
	public:
		explicit RealEngine(WindowSettings settings);
		~RealEngine();

		RealEngine(const RealEngine& other) = delete;
		RealEngine(RealEngine&& other) = delete;
		RealEngine& operator=(const RealEngine& other) = delete;
		RealEngine& operator=(RealEngine&& other) = delete;

		void Run(const std::function<void()>& load);

	private:
		WindowSettings m_Settings;

		void InitWindow();
		void InitImGui();
		void InitGame();
	};
}

#endif // MINIGIN_H