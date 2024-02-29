#include "stdafx.h"

//#include "GameObject.h"
#include "Scene.h"
#include "GameObject.h"
//#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"

#include "FPSCounter.h"
#include "InputManager.h"
#include "Rotator.h"
#include "Minigin.h"
#include "SceneManager.h"

void load()
{
	using namespace dae;

	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto& backGround = scene.CreateGameObject({});
	backGround.AddComponent<TextureComponent>("background_debug.png");

	auto& logo = scene.CreateGameObject();
	const auto pTextureComp = logo.AddComponent<TextureComponent>("logo.tga");
	const auto textureSize = pTextureComp->GetTexture()->GetSize();
	logo.GetTransform()->SetLocalPosition(640 / 2.f - textureSize.x / 2.f, 480 / 2.f - textureSize.y / 2.f);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto& title = scene.CreateGameObject();
	title.AddComponent<TextComponent>("Programming 4 Assignment", font);
	title.GetTransform()->SetLocalPosition(80, 40);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto& fpsCounter = scene.CreateGameObject();
	fpsCounter.AddComponent<FPSCounter>();
	fpsCounter.AddComponent<TextComponent>("00", font, SDL_Color{ 255,255,0,255 });;
	fpsCounter.GetTransform()->SetLocalPosition(0, 0);

	const auto characterOne = ResourceManager::GetInstance().LoadTexture("1.png");
	const auto characterTwo = ResourceManager::GetInstance().LoadTexture("2.png");
	const auto characterThree = ResourceManager::GetInstance().LoadTexture("3.png");

	auto& parent = scene.CreateGameObject();
	const auto textureComp = parent.AddComponent<TextureComponent>(characterOne);
	textureComp->SetRenderOffset(8, 8);
	parent.GetTransform()->SetLocalPosition(640 / 2.f + 20, 480 / 2.f + 20);
	//parent.GetTransform()->SetPivot(105, 105);
	parent.AddComponent<Rotator>(glm::vec2{ 640 / 2.f, 480 / 2.f }, 2.f);

	InputManager::GetInstance().m_ParentId = parent.GetId();

	auto& child = parent.CreateGameObject();
	const auto textureComp1 = child.AddComponent<TextureComponent>(characterTwo);
	textureComp1->SetRenderOffset(8, 8);
	child.GetTransform()->SetLocalPosition(20, 20);
	child.AddComponent<Rotator>(glm::vec2{ 0,0 }, 10.f);

	InputManager::GetInstance().m_ChildId = child.GetId();

	auto& secondChild = parent.CreateGameObject();
	const auto textureComp2 = secondChild.AddComponent<TextureComponent>(characterThree);
	textureComp2->SetRenderOffset(8, 8);
	secondChild.GetTransform()->SetLocalPosition(30, 30);
	secondChild.AddComponent<Rotator>(glm::vec2{ 0,0 }, 12.5f);

	std::cout << "Info: \n";
	std::cout << "Press 1 to detach child from parent\n";
	std::cout << "Press 2 to reattach child to parent\n";
	std::cout << "Press 3 to delete the child object\n";
	std::cout << "Press 4 to delete the parent object\n";
}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}