#include "PlayerEnemyPrefab.h"

#include <ResourceManager.h>
#include <GameObject.h>
#include <ColliderComponent.h>
#include <Colors.h>
#include <SpriteComponent.h>

#include "EnemyPlayer.h"
#include "Macros.h"
#include "Move.h"
#include "Interact.h"
#include "Pushable.h"

PlayerEnemyPrefab::PlayerEnemyPrefab(real::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos,
                                     PlayerNumber player)
		: Prefab(pOwner)
{
	Init(pos, mazePos, player);
}

PlayerEnemyPrefab::PlayerEnemyPrefab(real::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos,
	PlayerNumber player)
		: Prefab(pScene)
{
	Init(pos, mazePos, player);
}

void PlayerEnemyPrefab::Init(const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber player) const
{
	auto texture = real::ResourceManager::GetInstance().LoadTexture("textures/sno-bee/sno-bee_green.png");

	const auto go = GetGameObject();
	go->SetTag("Enemy");
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);

	real::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	spriteSheet.rows = 5;
	spriteSheet.columns = 8;
	spriteSheet.timePerAnimation = 0.2f;
	const auto spriteComponent = go->AddComponent<real::SpriteComponent>(std::move(spriteSheet));

	real::ColliderInfo info;
	info.pos = go->GetTransform()->GetWorldPosition();
	info.size = spriteComponent->GetSpriteSize();
	info.drawDebug = true;
	info.debugColor = real::Colors::pink;
	go->AddComponent<real::ColliderComponent>(info);

	const auto moveComponent = go->AddComponent<Move>(mazePos, Maze::BlockType::enemy, PLAYER_SPEED, true);
	moveComponent->BindAnimationToDirection(Direction::down, { 8, 9 });
	moveComponent->BindAnimationToDirection(Direction::left, { 10, 11 });
	moveComponent->BindAnimationToDirection(Direction::up, { 12, 13 });
	moveComponent->BindAnimationToDirection(Direction::right, { 14, 15 });
	moveComponent->Disable();

	const auto interactComponent = go->AddComponent<Interact>();
	interactComponent->BindAnimationToDirection(Direction::down, { 16, 17 });
	interactComponent->BindAnimationToDirection(Direction::left, { 18, 19 });
	interactComponent->BindAnimationToDirection(Direction::up, { 20, 21 });
	interactComponent->BindAnimationToDirection(Direction::right, { 22, 23 });

	go->AddComponent<EnemyPlayer>(player);
	go->AddComponent<Pushable>();

	spriteComponent->SelectSprite(8);
}
