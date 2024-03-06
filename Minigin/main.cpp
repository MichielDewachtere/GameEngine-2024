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

void load()
{
	using namespace dae;

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto backgroundTex = ResourceManager::GetInstance().LoadTexture("background.tga");
	auto& backGround = scene.CreateGameObject({});
	//backGround.AddComponent<TextureComponent>("background_debug.png");
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
	fpsCounter.AddComponent<TextComponent>("00", std::move(fontSmall), SDL_Color{ 255,255,0,255 });;
	fpsCounter.GetTransform()->SetLocalPosition(0, 0);

	auto characterOne = ResourceManager::GetInstance().LoadTexture("1.png");
	auto characterTwo = ResourceManager::GetInstance().LoadTexture("2.png");
	auto characterThree = ResourceManager::GetInstance().LoadTexture("3.png");

	auto& parent = scene.CreateGameObject();
	const auto textureComp = parent.AddComponent<TextureComponent>(std::move(characterOne));
	textureComp->SetRenderOffset(8, 8);
	parent.GetTransform()->SetLocalPosition(640 / 2.f + 20, 480 / 2.f + 20);
	parent.AddComponent<Rotator>(glm::vec2{ 640 / 2.f, 480 / 2.f }, 2.f);

	InputManager::GetInstance().m_ParentId = parent.GetId();

	auto& child = parent.CreateGameObject();
	const auto textureComp1 = child.AddComponent<TextureComponent>(std::move(characterTwo));
	textureComp1->SetRenderOffset(8, 8);
	child.GetTransform()->SetLocalPosition(20, 20);
	child.AddComponent<Rotator>(glm::vec2{ 0,0 }, 10.f);

	InputManager::GetInstance().m_ChildId = child.GetId();

	auto& secondChild = parent.CreateGameObject();
	const auto textureComp2 = secondChild.AddComponent<TextureComponent>(std::move(characterThree));
	textureComp2->SetRenderOffset(8, 8);
	secondChild.GetTransform()->SetLocalPosition(30, 30);
	secondChild.AddComponent<Rotator>(glm::vec2{ 0,0 }, 12.5f);

	//auto& imGuiTest = scene.CreateGameObject();
	//imGuiTest.AddComponent<TrashTheCache>();

	std::cout << "Info: \n";
	std::cout << "Press 1 to detach child from parent\n";
	std::cout << "Press 2 to reattach child to parent\n";
	std::cout << "Press 3 to delete the child object\n";
	std::cout << "Press 4 to delete the parent object\n";
}

int main(int, char* [])
{
	dae::Settings settings;
	settings.windowTitle = "Prog 4 Engine";
	settings.dataPath = "../Data/";
	settings.fps = 60;
	settings.width = 640;
	settings.height = 480;

	dae::Minigin engine(settings);
	engine.Run(load);
	return 0;
}