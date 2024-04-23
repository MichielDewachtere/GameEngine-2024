#include "HealthDisplay.h"

#include <GameObject.h>
#include <SpriteComponent.h>
#include <ResourceManager.h>

#include "Game.h"
#include "Macros.h"
#include "Scene.h"
#include "GameInfo.h"

HealthDisplay::HealthDisplay(real::GameObject* pOwner)
	: Component(pOwner)
{
	for (int i{ 0 }; i < m_AmountOfLives; ++i)
	{
		AddLifeTexture(i);
	}
}

void HealthDisplay::AddLife()
{
	AddLifeTexture(m_AmountOfLives);
	++m_AmountOfLives;
}

void HealthDisplay::RemoveLife()
{
	--m_AmountOfLives;
	if (m_AmountOfLives < 0)
	{
		GetOwner()->GetScene().FindGameObjectsWithTag(Tags::game).front()->GetComponent<Game>()->EndGame();
		return;
	}

	const auto childToRemove = GetOwner()->GetChildAt(m_AmountOfLives);
	childToRemove->GetComponent<real::SpriteComponent>()->PlayAnimation(0, 2, 0);
	childToRemove->Destroy(0.6f);
}

void HealthDisplay::AddLifeTexture(const int index) const
{
	auto texture = real::ResourceManager::GetInstance().LoadTexture("textures/pengo_lives_sheet.png");

	auto& go = GetOwner()->CreateGameObject();
	go.GetTransform()->SetLocalPosition(static_cast<float>(BLOCK_SIZE * PIXEL_SCALE * index), 0);
	go.GetTransform()->SetUniformScale(PIXEL_SCALE);

	real::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	spriteSheet.rows = 1;
	spriteSheet.columns = 3;
	spriteSheet.timePerAnimation = 0.2f;
	const auto spriteComponent = go.AddComponent<real::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->SelectSprite(0);
}
