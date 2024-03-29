#include "WallPrefab.h"

#include <memory>

#include <ResourceManager.h>
#include <GameObject.h>
#include <SpriteComponent.h>
#include <ColliderComponent.h>

#include "Colors.h"
#include "Macros.h"
#include "Wall.h"

WallPrefab::WallPrefab(dae::GameObject* pOwner, const glm::ivec2& pos, bool horizontal, WallOrientation orientation)
	: Prefab(pOwner)
{
	Init(pos, horizontal, orientation);
}

WallPrefab::WallPrefab(dae::Scene* pScene, const glm::ivec2& pos, bool horizontal, WallOrientation orientation)
	: Prefab(pScene)
{
	Init(pos, horizontal, orientation);
}

void WallPrefab::Init(const glm::ivec2& pos, bool horizontal, WallOrientation orientation)
{
	std::unique_ptr<dae::Texture2D> texture;
	if (horizontal)
		texture = dae::ResourceManager::GetInstance().LoadTexture("textures/wall_horizontal.png");
	else
		texture = dae::ResourceManager::GetInstance().LoadTexture("textures/wall_vertical.png");

	const auto go = GetGameObject();
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);

	dae::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	if (horizontal)
	{
		spriteSheet.rows = 3;
		spriteSheet.columns = 1;
	}
	else
	{
		spriteSheet.rows = 1;
		spriteSheet.columns = 3;
	}
	spriteSheet.timePerAnimation = 0.1f;
	const auto spriteComponent = go->AddComponent<dae::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->SelectSprite(0);

	const auto colliderComponent = go->AddComponent<dae::ColliderComponent>(go->GetTransform()->GetWorldPosition(), spriteComponent->GetSpriteSize());
	colliderComponent->EnableDrawDebug(true);
	colliderComponent->SetDebugColor(dae::Colors::purple);

	go->AddComponent<Wall>(orientation);
}
