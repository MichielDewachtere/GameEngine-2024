#include "stdafx.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TextComponent.h"

#include "TrashTheCache.h"
#include "Rotator.h"
#include "FPSCounter.h"
#include "MoveCommand.h"

void load()
{
	using namespace dae;

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto backgroundTex = ResourceManager::GetInstance().LoadTexture("background.tga");
	auto& backGround = scene.CreateGameObject({});
	backGround.AddComponent<TextureComponent>(std::move(backgroundTex));

	auto logoTex = ResourceManager::GetInstance().LoadTexture("logo.tga");
	auto& logo = scene.CreateGameObject();
	const auto pTextureComp = logo.AddComponent<TextureComponent>(std::move(logoTex));
	const auto textureSize = pTextureComp->GetTexture()->GetSize();
	logo.GetTransform()->SetLocalPosition(640 / 2.f - textureSize.x / 2.f, 480 / 2.f - textureSize.y / 2.f);

	auto fontBig = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto& title = scene.CreateGameObject();
	title.AddComponent<TextComponent>("Programming 4 Assignment", std::move(fontBig));
	title.GetTransform()->SetLocalPosition(80, 40);

	auto fontSmall = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto& fpsCounter = scene.CreateGameObject();
	fpsCounter.AddComponent<FPSCounter>();
	fpsCounter.AddComponent<TextComponent>("00", std::move(fontSmall), SDL_Color{ 255,255,0,255 });
	fpsCounter.GetTransform()->SetLocalPosition(0, 0);

	auto characterOne = ResourceManager::GetInstance().LoadTexture("1.png");
	auto characterTwo = ResourceManager::GetInstance().LoadTexture("2.png");
	auto characterThree = ResourceManager::GetInstance().LoadTexture("3.png");

	auto& parent = scene.CreateGameObject();
	const auto textureComp = parent.AddComponent<TextureComponent>(std::move(characterOne));
	textureComp->SetRenderOffset(8, 8);
	parent.GetTransform()->SetLocalPosition(640 / 2.f + 20, 480 / 2.f + 20);

	auto& child = parent.CreateGameObject();
	const auto textureComp1 = child.AddComponent<TextureComponent>(std::move(characterTwo));
	textureComp1->SetRenderOffset(8, 8);
	child.GetTransform()->SetLocalPosition(20, 20);
	child.AddComponent<Rotator>(glm::vec2{ 0,0 }, 10.f);

	auto& parent1 = scene.CreateGameObject();
	const auto textureComp2 = parent1.AddComponent<TextureComponent>(std::move(characterThree));
	textureComp2->SetRenderOffset(8, 8);
	parent1.GetTransform()->SetLocalPosition(640 / 2.f + 50, 480 / 2.f + 20);

	auto& input = InputManager::GetInstance();
	input.EnableGamePadInput(true);
	const auto id = input.RegisterGamePad();
	const auto map = input.AddInputMap("test");
	input.SetInputMapActive("test");
	map->AddKeyboardAction<MoveCommand>(0, KeyState::keyPressed, SDL_SCANCODE_W, &parent, glm::ivec2{ 0,-1 }, 25);
	map->AddKeyboardAction<MoveCommand>(1, KeyState::keyPressed, SDL_SCANCODE_A, &parent, glm::ivec2{ -1,0 }, 25);
	map->AddKeyboardAction<MoveCommand>(2, KeyState::keyPressed, SDL_SCANCODE_S, &parent, glm::ivec2{ 0,1 },	25);
	map->AddKeyboardAction<MoveCommand>(3, KeyState::keyPressed, SDL_SCANCODE_D, &parent, glm::ivec2{ 1,0 },	25);

	map->AddKeyboardAction<TestCommand>(4, KeyState::keyUp, SDL_SCANCODE_1);
	map->AddKeyboardAction<TestCommand>(5, KeyState::keyDown, SDL_SCANCODE_2);
	map->AddKeyboardAction<TestCommand>(6, KeyState::keyPressed, SDL_SCANCODE_3);

	map->AddGamePadAction<MoveCommand>(id, KeyState::keyPressed, GamePad::Button::dPadUp,		&parent1, glm::ivec2{ 0,-1 },	50);
	map->AddGamePadAction<MoveCommand>(id, KeyState::keyPressed, GamePad::Button::dPadLeft,		&parent1, glm::ivec2{ -1,0 },	50);
	map->AddGamePadAction<MoveCommand>(id, KeyState::keyPressed, GamePad::Button::dPadDown,		&parent1, glm::ivec2{ 0,1	},	50);
	map->AddGamePadAction<MoveCommand>(id, KeyState::keyPressed, GamePad::Button::dPadRight,	&parent1, glm::ivec2{ 1,0 },	50);
}

int main(int, char* [])
{
	dae::Settings settings;
	settings.windowTitle = "Prog 4 Engine";
	settings.dataPath = "../Data/";
	settings.fps = 60;
	settings.width = 640;
	settings.height = 480;

	try
	{
		dae::Minigin engine(settings);
		engine.Run(load);
	}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}