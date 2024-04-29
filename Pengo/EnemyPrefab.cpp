#include "EnemyPrefab.h"

#include <GameObject.h>
#include <ColliderComponent.h>
#include <Colors.h>
#include <ResourceManager.h>
#include <SpriteComponent.h>

#include "Pushable.h"
#include "Enemy.h"
#include "Macros.h"
#include "Move.h"

EnemyPrefab::EnemyPrefab(real::GameObject* pOwner, const glm::ivec2& pos, const glm::ivec2& mazePos)
	: Prefab(pOwner)
{
	Init(pos, mazePos);
}

EnemyPrefab::EnemyPrefab(real::Scene* pScene, const glm::ivec2& pos, const glm::ivec2& mazePos)
	: Prefab(pScene)
{
	Init(pos, mazePos);
}

void EnemyPrefab::Init(const glm::ivec2& pos, const glm::ivec2& mazePos) const
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
	spriteComponent->SelectSprite(2);

	real::ColliderInfo info;
	info.pos = go->GetTransform()->GetWorldPosition();
	info.size = spriteComponent->GetSpriteSize();
	info.debugColor = real::Colors::purple;
	info.drawDebug = true;
	go->AddComponent<real::ColliderComponent>(info);

	const auto moveComponent = go->AddComponent<Move>(mazePos, Maze::BlockType::enemy, 75.f, true);
	moveComponent->BindAnimationToDirection(Direction::down, { 8, 9 });
	moveComponent->BindAnimationToDirection(Direction::left, { 10, 11 });
	moveComponent->BindAnimationToDirection(Direction::up, { 12, 13 });
	moveComponent->BindAnimationToDirection(Direction::right, { 14, 15 });

	go->AddComponent<Enemy>();
	go->AddComponent<Pushable>();
}
