#include "IcePrefab.h"

#include <memory>

#include <ResourceManager.h>
#include <GameObject.h>
#include <TextureComponent.h>
#include <ColliderComponent.h>

#include "Colors.h"
#include "Macros.h"

IcePrefab::IcePrefab(dae::GameObject* pOwner, const glm::ivec2& pos)
	: Prefab(pOwner)
{
	Init(pos);
}

IcePrefab::IcePrefab(dae::Scene* pScene, const glm::ivec2& pos)
	: Prefab(pScene)
{
	Init(pos);
}

void IcePrefab::Init(const glm::ivec2& pos)
{
	auto texture = dae::ResourceManager::GetInstance().LoadTexture("textures/ice_cube.png");

	const auto go = GetGameObject();
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);
	const auto textComp = go->AddComponent<dae::TextureComponent>(std::move(texture));
	const auto colliderComponent = go->AddComponent<dae::ColliderComponent>(go->GetTransform()->GetWorldPosition(), textComp->GetTexture()->GetSize());
	colliderComponent->EnableDrawDebug(true);
	colliderComponent->SetDebugColor(dae::Colors::cyan);
	// TODO: Add ice functionality
}
