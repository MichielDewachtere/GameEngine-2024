#include "PlayerEnemyPrefab.h"

#include <ResourceManager.h>
#include <GameObject.h>
#include <ColliderComponent.h>
#include <Colors.h>
#include <SpriteComponent.h>

#include "Macros.h"
#include "Move.h"
#include "Interact.h"
#include "Player.h"

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

void PlayerEnemyPrefab::Init(const glm::ivec2& pos, const glm::ivec2& mazePos, PlayerNumber /*player*/) const
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
	spriteComponent->SelectSprite(16);

	real::ColliderInfo info;
	info.pos = go->GetTransform()->GetWorldPosition();
	info.size = spriteComponent->GetSpriteSize();
	info.drawDebug = true;
	info.debugColor = real::Colors::pink;
	go->AddComponent<real::ColliderComponent>(info);

	const auto moveComponent = go->AddComponent<Move>(mazePos, Maze::BlockType::enemy, PLAYER_SPEED, true);
	moveComponent->BindAnimationToDirection(Direction::down, { 16, 17 });
	moveComponent->BindAnimationToDirection(Direction::left, { 18, 19 });
	moveComponent->BindAnimationToDirection(Direction::up, { 20, 21 });
	moveComponent->BindAnimationToDirection(Direction::right, { 22, 23 });
	moveComponent->Disable();

	go->AddComponent<Interact>();
	//go->AddComponent<Player>(player);
}
