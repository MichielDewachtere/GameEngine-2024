#include "stdafx.h"
#include "Minigin.h"

#include "GameTime.h"
#include "InputManager.h"
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

	SDL_IMAGE_VERSION(&version);
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

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	GameTime::GetInstance().Init();

	Logger::Initialize();

	Renderer::GetInstance().Init(g_window);
	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	SceneManager::GetInstance().Destroy();
	Renderer::GetInstance().Destroy();
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

	auto lastTime = std::chrono::high_resolution_clock::now();
	constexpr int desiredFps = 60;
	constexpr float desiredFrameTime = 1000.f / static_cast<float>(desiredFps);
	//float lag = 0.0f;

	while (doContinue)
	{
		time.Update();

		const auto currentTime = std::chrono::high_resolution_clock::now();

		//// Fixed Update
		//lastTime = currentTime;

		//constexpr float fixedTimeStep = 0.02f;
		//lag += time.GetElapsed();

		//while (lag >= fixedTimeStep)
		//{
		//	sceneManager.FixedUpdate();
		//	lag -= fixedTimeStep;
		//}

		doContinue = input.ProcessInput();

		sceneManager.Update();
		renderer.Render();

		constexpr auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<float, std::milli>(desiredFrameTime));
		const auto sleepTime = currentTime + frameDuration - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleepTime);
	}
}
