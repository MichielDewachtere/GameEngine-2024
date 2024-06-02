#include "EggCounter.h"

#include <SceneManager.h>
#include <SpriteComponent.h>
#include <ResourceManager.h>

#include "EnemyHandler.h"
#include "GameInfo.h"
#include "Macros.h"

EggCounter::EggCounter(real::GameObject* pOwner)
	: Component(pOwner)
{
	real::SceneManager::GetInstance().exitScene.AddObserver(this);
	real::SceneManager::GetInstance().loadScene.AddObserver(this);
}

EggCounter::~EggCounter()
{
	real::SceneManager::GetInstance().exitScene.RemoveObserver(this);
	real::SceneManager::GetInstance().loadScene.RemoveObserver(this);
}

void EggCounter::Start()
{
	for (int i = 0; i < EnemyHandler::GetAmountOfEnemies(); ++i)
		InitEgg(i);
}

void EggCounter::HandleEvent(real::SceneEvents event, real::Scene* scene)
{
	if (scene->GetName().find("level") == std::string::npos)
		return;

	if (EnemyHandler::GetAmountOfEnemies() == 0)
		return;

	if (event == real::SceneEvents::load)
	{
		scene->FindGameObjectsWithTag(Tags::game).front()->GetComponent<EnemyHandler>()->enemySpawned.AddObserver(this);
	}
	else if (event == real::SceneEvents::exit)
	{
		for (const auto& go : GetOwner()->GetChildren())
		{
			go->Destroy();
		}

		scene->FindGameObjectsWithTag(Tags::game).front()->GetComponent<EnemyHandler>()->enemySpawned.RemoveObserver(this);
	}
}

void EggCounter::HandleEvent()
{
	const auto children = GetOwner()->GetChildren();

	for (auto it = children.end() - 1; it != children.begin(); --it)
	//for (const auto& c : GetOwner()->GetChildren())
	{
		if (std::ranges::find(m_AlreadyDestroyed, (*it)->GetId()) != m_AlreadyDestroyed.end())
			continue;

		m_AlreadyDestroyed.push_back((*it)->GetId());
		(*it)->GetComponent<real::SpriteComponent>()->PlayAnimation(0, 2, 0);
		(*it)->Destroy(1.f);
		break;
	}
}

void EggCounter::InitEgg(const int id) const
{
	auto& egg = GetOwner()->CreateGameObject();
	egg.GetTransform()->SetLocalPosition(static_cast<float>(8 * PIXEL_SCALE * id), 0);
	egg.GetTransform()->SetUniformScale(PIXEL_SCALE);

	real::SpriteSheet sprite;
	sprite.pTexture = real::ResourceManager::GetInstance().LoadTexture("textures/egg_counter_sheet.png");
	sprite.columns = 3;
	sprite.rows = 1;
	sprite.timePerAnimation = 0.5f;
	const auto spriteComponent = egg.AddComponent<real::SpriteComponent>(std::move(sprite));
	spriteComponent->PlayAnimation(0, 1);
}