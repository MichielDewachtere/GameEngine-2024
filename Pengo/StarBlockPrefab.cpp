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

StarBlockPrefab::StarBlockPrefab(dae::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos)
	: Prefab(pOwner)
{
	Init(pos, mazePos);
}

StarBlockPrefab::StarBlockPrefab(dae::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos)
	: Prefab(pScene)
{
	Init(pos, mazePos);
}

void StarBlockPrefab::Init(const glm::ivec2& pos, const glm::ivec2& mazePos)
{
	auto texture = dae::ResourceManager::GetInstance().LoadTexture("textures/block_sheet.png");

	const auto go = GetGameObject();
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);

	dae::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	spriteSheet.columns = 9;
	spriteSheet.rows = 4;
	spriteSheet.timePerAnimation = 0.2f;
	const auto spriteComponent = go->AddComponent<dae::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->SelectSprite(9);

	const auto colliderComponent = go->AddComponent<dae::ColliderComponent>(go->GetTransform()->GetWorldPosition(), spriteComponent->GetSpriteSize());
	colliderComponent->EnableDrawDebug(true);
	colliderComponent->SetDebugColor(dae::Colors::yellow);

	go->AddComponent<Move>(mazePos, Maze::BlockType::star, 300.f, false);
	go->AddComponent<Pushable>();
}
