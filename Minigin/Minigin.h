#ifndef MINIGIN_H
#define MINIGIN_H

#include <functional>
#include <stdint.h>
#include <string>

namespace dae
{
	struct Settings
	{
		uint32_t width = 640, height = 480, fps = 60;
		float frameTime = 0.016f;
		std::string windowTitle, dataPath;
	};

	class Minigin
	{
	public:
		explicit Minigin(Settings settings);
		~Minigin();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

		void Run(const std::function<void()>& load);

	private:
		Settings m_Settings;

		void InitWindow();
		void InitImGui();
		void InitGame();
	};
}

#endif // MINIGIN_H