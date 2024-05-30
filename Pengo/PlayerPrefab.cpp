#include "PlayerPrefab.h"

#include <GameObject.h>
#include <ColliderComponent.h>
#include <Colors.h>
#include <ResourceManager.h>
#include <SpriteComponent.h>

#include "Macros.h"
#include "Move.h"
#include "Interact.h"
#include "Player.h"

PlayerPrefab::PlayerPrefab(real::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber player)
	: Prefab(pOwner)
{
	Init(pos, mazePos, player);
}

PlayerPrefab::PlayerPrefab(real::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber player)
	: Prefab(pScene)
{
	Init(pos, mazePos, player);
}

void PlayerPrefab::Init(const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber player) const
{
	auto texture = real::ResourceManager::GetInstance().LoadTexture("textures/pengo/pengo_red.png");

	const auto go = GetGameObject();
	go->SetTag("Player");
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);

	real::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	spriteSheet.rows = 4;
	spriteSheet.columns = 8;
	spriteSheet.timePerAnimation = 0.2f;
	const auto spriteComponent = go->AddComponent<real::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->SelectSprite(0);

	real::ColliderInfo info;
	info.pos = go->GetTransform()->GetWorldPosition();
	info.size = spriteComponent->GetSpriteSize();
	info.drawDebug = true;
	info.debugColor = real::Colors::appelblauwzeegroen;
	go->AddComponent<real::ColliderComponent>(info);

	const auto moveComponent = go->AddComponent<Move>(mazePos, Maze::BlockType::player, PLAYER_SPEED, true);
	moveComponent->BindAnimationToDirection(Direction::down, { 0, 1 });
	moveComponent->BindAnimationToDirection(Direction::left, { 2, 3 });
	moveComponent->BindAnimationToDirection(Direction::up, { 4, 5 });
	moveComponent->BindAnimationToDirection(Direction::right, { 6, 7 });
	moveComponent->Disable();

	const auto interactComponent = go->AddComponent<Interact>();
	interactComponent->BindAnimationToDirection(Direction::down, { 8,9 });
	interactComponent->BindAnimationToDirection(Direction::left, { 10,11 });
	interactComponent->BindAnimationToDirection(Direction::up, { 12,13 });
	interactComponent->BindAnimationToDirection(Direction::right, { 14,15 });

	go->AddComponent<Player>(player, false);
}
