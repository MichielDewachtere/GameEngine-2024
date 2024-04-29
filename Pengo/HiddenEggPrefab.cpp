#include "HiddenEggPrefab.h"

#include <memory>

#include <ResourceManager.h>
#include <GameObject.h>
#include <SpriteComponent.h>
#include <ColliderComponent.h>
#include <Colors.h>

#include "HiddenEgg.h"
#include "IcePrefab.h"
#include "Macros.h"

HiddenEggPrefab::HiddenEggPrefab(real::GameObject* pOwner)
	: Prefab(pOwner)
{
	Init();
}

HiddenEggPrefab::HiddenEggPrefab(real::Scene* pScene)
	: Prefab(pScene)
{
	Init();
}

void HiddenEggPrefab::Init() const
{
	auto texture = real::ResourceManager::GetInstance().LoadTexture("textures/egg_sheet.png");

	const auto go = GetGameObject();
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);

	real::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	spriteSheet.rows = 2;
	spriteSheet.columns = 3;
	spriteSheet.timePerAnimation = 0.02f;
	const auto spriteComponent = go->AddComponent<real::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->Disable();

	real::ColliderInfo info;
	info.pos = go->GetTransform()->GetWorldPosition();
	info.size = spriteComponent->GetSpriteSize();
	info.drawDebug = true;
	info.debugColor = real::Colors::red;
	go->AddComponent<real::ColliderComponent>(info);

	go->AddComponent<HiddenEgg>();
}
