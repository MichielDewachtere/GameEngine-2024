#include "PlayerPrefab.h"

#include <GameObject.h>
#include <ColliderComponent.h>
#include <Colors.h>
#include <ResourceManager.h>
#include <SpriteComponent.h>

#include "Macros.h"
#include "Move.h"
#include "Interact.h"

PlayerPrefab::PlayerPrefab(dae::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos)
	: Prefab(pOwner)
{
	Init(pos, mazePos);
}

PlayerPrefab::PlayerPrefab(dae::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos)
	: Prefab(pScene)
{
	Init(pos, mazePos);
}

void PlayerPrefab::Init(const glm::ivec2& pos, const glm::ivec2& mazePos)
{
	auto texture = dae::ResourceManager::GetInstance().LoadTexture("textures/pengo/pengo_red.png");

	const auto go = GetGameObject();
	go->SetTag("Player");
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);

	dae::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	spriteSheet.rows = 4;
	spriteSheet.columns = 8;
	spriteSheet.timePerAnimation = 0.2f;
	const auto spriteComponent = go->AddComponent<dae::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->SelectSprite(0);
	//spriteComponent->PlayAnimation(0, 2);

	const auto colliderComponent = go->AddComponent<dae::ColliderComponent>(go->GetTransform()->GetWorldPosition(), spriteComponent->GetSpriteSize());
	colliderComponent->EnableDrawDebug(true);
	colliderComponent->SetDebugColor(dae::Colors::appelblauwzeegroen);

	const auto moveComponent = go->AddComponent<Move>(mazePos, Maze::BlockType::player, PLAYER_SPEED, true);
	moveComponent->BindAnimationToDirection(Direction::down, { 0, 1 });
	moveComponent->BindAnimationToDirection(Direction::left, { 2, 3 });
	moveComponent->BindAnimationToDirection(Direction::up, { 4, 5 });
	moveComponent->BindAnimationToDirection(Direction::right, { 6, 7 });
	moveComponent->Disable();

	go->AddComponent<Interact>();
}
