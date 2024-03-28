#include "IcePrefab.h"

#include <memory>

#include <ResourceManager.h>
#include <GameObject.h>
#include <SpriteComponent.h>
#include <ColliderComponent.h>

#include "Colors.h"
#include "HiddenEggPrefab.h"
#include "IceBlock.h"
#include "Macros.h"
#include "Move.h"
#include "Pushable.h"

IcePrefab::IcePrefab(dae::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos, bool hidesEgg)
	: Prefab(pOwner)
{
	Init(pos, mazePos, hidesEgg);
}

IcePrefab::IcePrefab(dae::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos, bool hidesEgg)
	: Prefab(pScene)
{
	Init(pos, mazePos, hidesEgg);
}

void IcePrefab::Init(const glm::ivec2& pos, const glm::ivec2& mazePos, bool hidesEgg)
{
	auto texture = dae::ResourceManager::GetInstance().LoadTexture("textures/block_sheet.png");

	const auto go = GetGameObject();
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);

	dae::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	spriteSheet.columns = 9;
	spriteSheet.rows = 4;
	spriteSheet.timePerAnimation = 0.1f;
	const auto spriteComponent = go->AddComponent<dae::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->SelectSprite(0);

	const auto colliderComponent = go->AddComponent<dae::ColliderComponent>(go->GetTransform()->GetWorldPosition(), spriteComponent->GetSpriteSize());
	colliderComponent->EnableDrawDebug(true);
	colliderComponent->SetDebugColor(dae::Colors::cyan);

	go->AddComponent<Move>(mazePos, Maze::BlockType::ice, PUSH_SPEED, false);
	go->AddComponent<IceBlock>(hidesEgg);
	go->AddComponent<Pushable>();
}
