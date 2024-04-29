#include "WallPrefab.h"

#include <memory>

#include <ResourceManager.h>
#include <GameObject.h>
#include <SpriteComponent.h>
#include <ColliderComponent.h>

#include "Colors.h"
#include "Macros.h"
#include "Wall.h"

WallPrefab::WallPrefab(real::GameObject* pOwner, const glm::ivec2& pos, bool horizontal, WallOrientation orientation)
	: Prefab(pOwner)
{
	Init(pos, horizontal, orientation);
}

WallPrefab::WallPrefab(real::Scene* pScene, const glm::ivec2& pos, bool horizontal, WallOrientation orientation)
	: Prefab(pScene)
{
	Init(pos, horizontal, orientation);
}

void WallPrefab::Init(const glm::ivec2& pos, bool horizontal, WallOrientation orientation)
{
	std::unique_ptr<real::Texture2D> texture;
	if (horizontal)
		texture = real::ResourceManager::GetInstance().LoadTexture("textures/wall_horizontal.png");
	else
		texture = real::ResourceManager::GetInstance().LoadTexture("textures/wall_vertical.png");

	const auto go = GetGameObject();
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);

	real::SpriteSheet spriteSheet;
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
	const auto spriteComponent = go->AddComponent<real::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->SelectSprite(0);

	real::ColliderInfo info;
	info.pos = go->GetTransform()->GetWorldPosition();
	info.size = spriteComponent->GetSpriteSize();
	info.drawDebug = true;
	info.debugColor = real::Colors::purple;
	go->AddComponent<real::ColliderComponent>(info);

	go->AddComponent<Wall>(orientation);
}
