#include "RealEngine.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_version.h>
#include <SDL_video.h>

#include <thread>

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "implot.h"

#include "GameTime.h"
#include "InputManager.h"
#include "Locator.h"
#include "Logger.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SDLAudio.h"
#include "LogAudio.h"

void PrintSDLVersion()
{
	SDL_version version;
	SDL_VERSION(&version)
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version)
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

real::RealEngine::RealEngine(WindowSettings settings)
	: m_Settings(std::move(settings))
{
	m_Settings.frameTime = 1.f / static_cast<float>(m_Settings.fps);

	PrintSDLVersion();
	InitWindow(m_Settings.windowTitle, m_Settings.width, m_Settings.height, 0);
	InitGame();
	InitImGui();

#ifdef NDEBUG
	Locator::RegisterAudioSystem(new SDLAudio());
#else
	Locator::RegisterAudioSystem(new LogAudio(new SDLAudio()));
#endif 
}

real::RealEngine::~RealEngine()
{
	SceneManager::GetInstance().Destroy();
	Renderer::GetInstance().Destroy();

	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
}

void real::RealEngine::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = GameTime::GetInstance();

	bool doContinue = true;

#pragma region Fixed Update
	//auto lastTime = std::chrono::high_resolution_clock::now();
	//float lag = 0.0f;
#pragma endregion Fixed Update

	//const float desiredFrameTime = 1000.f / static_cast<float>(m_Settings.fps);

	while (doContinue)
	{
		time.Update();
		const auto currentTime = std::chrono::high_resolution_clock::now();

#pragma region Fixed Update
		//lastTime = currentTime;
		
		//constexpr float fixedTimeStep = 0.02f;
		//lag += time.GetElapsed();

		//while (lag >= fixedTimeStep)
		//{
		//	sceneManager.FixedUpdate();
		//	lag -= fixedTimeStep;
		//}
#pragma endregion Fixed Update

		doContinue = input.ProcessInput();

		sceneManager.Update();
		Locator::GetAudioSystem().Update();

		renderer.Render();

		auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<float>(m_Settings.frameTime));
		const auto sleepTime = currentTime + frameDuration - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}
}

void real::RealEngine::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(GetWindow(), Renderer::GetInstance().GetSDLRenderer());
	ImGui_ImplSDLRenderer2_Init(Renderer::GetInstance().GetSDLRenderer());
}

void real::RealEngine::InitGame() const
{
	GameTime::GetInstance().Init();

	Logger::Initialize();

	Renderer::GetInstance().Init(GetWindow());
	ResourceManager::GetInstance().Init(m_Settings.dataPath);
}
