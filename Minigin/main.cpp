#include "stdafx.h"

//#include "GameObject.h"
#include "Scene.h"
#include "GameObject.h"
//#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"

#include "FPSCounter.h"
#include "Minigin.h"

void load()
{
	using namespace dae;
	
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto& backGround = scene.CreateGameObject();
	backGround.AddComponent<TextureComponent>("background.tga");

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
}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}