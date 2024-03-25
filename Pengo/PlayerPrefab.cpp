#include "PlayerPrefab.h"

#include <GameObject.h>
#include <ColliderComponent.h>
#include <Colors.h>
#include <ResourceManager.h>
#include <TextureComponent.h>

#include "Macros.h"

PlayerPrefab::PlayerPrefab(dae::GameObject* pOwner, const glm::ivec2& pos)
	: Prefab(pOwner)
{
	Init(pos);
}

PlayerPrefab::PlayerPrefab(dae::Scene* pScene, const glm::ivec2& pos)
	: Prefab(pScene)
{
	Init(pos);
}

void PlayerPrefab::Init(const glm::ivec2& pos)
{
	auto texture = dae::ResourceManager::GetInstance().LoadTexture("textures/pengo.png");

	const auto go = GetGameObject();
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);
	const auto textComp = go->AddComponent<dae::TextureComponent>(std::move(texture));
	const auto colliderComponent = go->AddComponent<dae::ColliderComponent>(go->GetTransform()->GetWorldPosition(), textComp->GetTexture()->GetSize());
	colliderComponent->EnableDrawDebug(true);
	colliderComponent->SetDebugColor(dae::Colors::appelblauwzeegroen);
}
