#include "LevelDisplayBottom.h"

#include <SceneManager.h>
#include <TextComponent.h>
#include <SpriteComponent.h>
#include <ResourceManager.h>

#include "Game.h"
#include "Macros.h"

LevelDisplayBottom::LevelDisplayBottom(real::GameObject* pOwner)
	: Component(pOwner)
{
	real::SceneManager::GetInstance().loadScene.AddObserver(this);

	m_pTextComponent = GetOwner()->GetComponent<real::TextComponent>();
	for (int i{ 0 }; i < 4; ++i)
		InitAct(i);
}

LevelDisplayBottom::~LevelDisplayBottom()
{
	real::SceneManager::GetInstance().loadScene.RemoveObserver(this);
}

void LevelDisplayBottom::HandleEvent(real::SceneEvents, real::Scene* scene)
{
	if (scene->GetName().find("level") == std::string::npos)
		return;

	const auto level = Game::GetCurrentLevel();

	m_pTextComponent->SetText("act " + std::to_string(level));

	Reset();
	const int amount = level % 5;
	SetActive(amount);
}

void LevelDisplayBottom::Reset() const
{
	for (const auto& c : GetOwner()->GetChildren())
	{
		c->SetIsActive(false, true);
	}
}

void LevelDisplayBottom::InitAct(int id) const
{
	auto texture = real::ResourceManager::GetInstance().LoadTexture("textures/act_sheet.png");

	auto& go = GetOwner()->CreateGameObject();
	real::SpriteSheet spriteSheet;
	spriteSheet.pTexture = std::move(texture);
	spriteSheet.rows = 1;
	spriteSheet.columns = 2;
	spriteSheet.timePerAnimation = 0;

	const auto spriteComponent = go.AddComponent<real::SpriteComponent>(std::move(spriteSheet));
	spriteComponent->SelectSprite(0);

	go.GetTransform()->SetLocalPosition(150.f + static_cast<float>(spriteComponent->GetSpriteSize().x * PIXEL_SCALE * id), -static_cast<float>(spriteComponent->GetSpriteSize().y) - 8);
	go.GetTransform()->SetUniformScale(PIXEL_SCALE);
	go.SetIsActive(false, true);
}

void LevelDisplayBottom::SetActive(int amount) const
{
	for (int i{ 0 }; i < amount; ++i)
	{
		GetOwner()->GetChildAt(i)->SetIsActive(true, true);
	}
}
