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

HiddenEggPrefab::HiddenEggPrefab(dae::GameObject* pOwner)
	: Prefab(pOwner)
{
	Init();
}

HiddenEggPrefab::HiddenEggPrefab(dae::Scene* pScene)
	: Prefab(pScene)
{
	Init();
}

void HiddenEggPrefab::Init()
{
	auto texture = dae::ResourceManager::GetInstance().LoadTexture("textures/egg_sheet.png");

	const auto go = GetGameObject();
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);

	dae::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	spriteSheet.rows = 1;
	spriteSheet.columns = 3;
	spriteSheet.timePerAnimation = 0.02f;
	const auto spriteComponent = go->AddComponent<dae::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->Disable();

	const auto colliderComponent = go->AddComponent<dae::ColliderComponent>(go->GetTransform()->GetWorldPosition(), spriteComponent->GetSpriteSize());
	colliderComponent->EnableDrawDebug(true);
	colliderComponent->SetDebugColor(dae::Colors::red);

	go->AddComponent<HiddenEgg>();
}
