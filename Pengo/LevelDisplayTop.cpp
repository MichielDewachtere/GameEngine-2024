#include "LevelDisplayTop.h"

#include <SceneManager.h>
#include <ResourceManager.h>
#include <SpriteComponent.h>

#include "Game.h"
#include "Macros.h"

LevelDisplayTop::LevelDisplayTop(real::GameObject* pOwner)
	: Component(pOwner)
{
	real::SceneManager::GetInstance().loadScene.AddObserver(this);
}

LevelDisplayTop::~LevelDisplayTop()
{
	real::SceneManager::GetInstance().loadScene.RemoveObserver(this);
}

void LevelDisplayTop::HandleEvent(real::SceneEvents, real::Scene* scene)
{
	if (scene->GetName().find("level") == std::string::npos)
		return;

	const int i = Game::GetCurrentLevel() / 5;
	if (i > static_cast<int>(GetOwner()->GetChildCount()))
	{
		auto texture = real::ResourceManager::GetInstance().LoadTexture("textures/act_sheet.png");

		auto& go = GetOwner()->CreateGameObject();
		real::SpriteSheet spriteSheet;
		spriteSheet.pTexture = std::move(texture);
		spriteSheet.rows = 1;
		spriteSheet.columns = 2;
		spriteSheet.timePerAnimation = 0;

		const auto spriteComponent = go.AddComponent<real::SpriteComponent>(std::move(spriteSheet));
		spriteComponent->SelectSprite(1);

		go.GetTransform()->SetLocalPosition(-static_cast<float>(spriteComponent->GetSpriteSize().x * PIXEL_SCALE * i), 0);
		go.GetTransform()->SetUniformScale(PIXEL_SCALE);
	}
}