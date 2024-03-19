#include "Minigin.h"

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
#include "Logger.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

SDL_Window* g_window{};

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

dae::Minigin::Minigin(Settings settings)
	: m_Settings(std::move(settings))
{
	m_Settings.frameTime = 1.f / static_cast<float>(m_Settings.fps);

	InitWindow();
	InitGame();
	InitImGui();
}

dae::Minigin::~Minigin()
{
	SceneManager::GetInstance().Destroy();
	Renderer::GetInstance().Destroy();

	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();

	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
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
		renderer.Render();

		auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<float>(m_Settings.frameTime));
		const auto sleepTime = currentTime + frameDuration - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}
}

void dae::Minigin::InitWindow()
{
	PrintSDLVersion();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		m_Settings.windowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		static_cast<int>(m_Settings.width),
		static_cast<int>(m_Settings.height),
		SDL_WINDOW_OPENGL
	);

	if (g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
}

void dae::Minigin::InitImGui()
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
	ImGui_ImplSDL2_InitForSDLRenderer(g_window, Renderer::GetInstance().GetSDLRenderer());
	ImGui_ImplSDLRenderer2_Init(Renderer::GetInstance().GetSDLRenderer());
}

void dae::Minigin::InitGame()
{
	GameTime::GetInstance().Init();

	Logger::Initialize();

	Renderer::GetInstance().Init(g_window);
	ResourceManager::GetInstance().Init(m_Settings.dataPath);
}
