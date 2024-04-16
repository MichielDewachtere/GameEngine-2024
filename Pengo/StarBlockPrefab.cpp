#include "StarBlockPrefab.h"

#include <memory>

#include <ResourceManager.h>
#include <GameObject.h>
#include <SpriteComponent.h>
#include <ColliderComponent.h>
#include <Colors.h>

#include "Macros.h"
#include "Maze.h"
#include "Move.h"
#include "Pushable.h"

StarBlockPrefab::StarBlockPrefab(real::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos)
	: Prefab(pOwner)
{
	Init(pos, mazePos);
}

StarBlockPrefab::StarBlockPrefab(real::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos)
	: Prefab(pScene)
{
	Init(pos, mazePos);
}

void StarBlockPrefab::Init(const glm::ivec2& pos, const glm::ivec2& mazePos)
{
	auto texture = real::ResourceManager::GetInstance().LoadTexture("textures/block_sheet.png");

	const auto go = GetGameObject();
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);

	real::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	spriteSheet.columns = 9;
	spriteSheet.rows = 4;
	spriteSheet.timePerAnimation = 0.2f;
	const auto spriteComponent = go->AddComponent<real::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->SelectSprite(9);

	const auto colliderComponent = go->AddComponent<real::ColliderComponent>(go->GetTransform()->GetWorldPosition(), spriteComponent->GetSpriteSize());
	colliderComponent->EnableDrawDebug(true);
	colliderComponent->SetDebugColor(real::Colors::yellow);

	go->AddComponent<Move>(mazePos, Maze::BlockType::star, 300.f, false);
	go->AddComponent<Pushable>();
}
