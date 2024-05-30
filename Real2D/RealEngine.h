#ifndef MINIGIN_H
#define MINIGIN_H

#include <cstdint>

#include <EngineBase.h>

namespace real
{
	struct WindowSettings
	{
		uint32_t width = 640, height = 480, fps = 60;
		float frameTime = 0.016f;
		std::string windowTitle, dataPath;
	};

	class RealEngine final : public EngineBase
	{
	public:
		explicit RealEngine(WindowSettings settings);
		virtual ~RealEngine() override;

		RealEngine(const RealEngine& other) = delete;
		RealEngine(RealEngine&& other) = delete;
		RealEngine& operator=(const RealEngine& other) = delete;
		RealEngine& operator=(RealEngine&& other) = delete;

		virtual void Run(const std::function<void()>& load) override;

	private:
		WindowSettings m_Settings;

		void InitImGui();
		void InitGame() const;
	};
}

#endif // MINIGIN_H