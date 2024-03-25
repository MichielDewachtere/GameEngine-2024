#include "WallPrefab.h"

#include <memory>

#include <ResourceManager.h>
#include <GameObject.h>
#include <TextureComponent.h>
#include <ColliderComponent.h>

#include "Colors.h"
#include "Macros.h"

WallPrefab::WallPrefab(dae::GameObject* pOwner, const glm::ivec2& pos, bool horizontal)
	: Prefab(pOwner)
{
	Init(pos, horizontal);
}

WallPrefab::WallPrefab(dae::Scene* pScene, const glm::ivec2& pos, bool horizontal)
	: Prefab(pScene)
{
	Init(pos, horizontal);
}

void WallPrefab::Init(const glm::ivec2& pos, bool horizontal)
{
	std::unique_ptr<dae::Texture2D> texture;
	if (horizontal)
		texture = dae::ResourceManager::GetInstance().LoadTexture("textures/wall_horizontal_temp.png");
	else
		texture = dae::ResourceManager::GetInstance().LoadTexture("textures/wall_vertical_temp.png");

	const auto go = GetGameObject();
	go->GetTransform()->SetLocalPosition(pos);
	go->GetTransform()->SetUniformScale(PIXEL_SCALE);
	const auto textComp = go->AddComponent<dae::TextureComponent>(std::move(texture));
	const auto colliderComponent = go->AddComponent<dae::ColliderComponent>(go->GetTransform()->GetWorldPosition(), textComp->GetTexture()->GetSize());
	colliderComponent->EnableDrawDebug(true);
	colliderComponent->SetDebugColor(dae::Colors::purple);
	// TODO: Add functionality
}
