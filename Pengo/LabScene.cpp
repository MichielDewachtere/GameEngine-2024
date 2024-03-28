#include "LabScene.h"

#include <memory>

#include <ColliderComponent.h>
#include <SceneManager.h>
#include <InputManager.h>
#include <ResourceManager.h>
#include <TextureComponent.h>
#include <TextComponent.h>

#include "TrashTheCache.h"
#include "Rotator.h"
#include "FPSCounter.h"
#include "Player.h"
#include "LivesDisplay.h"
#include "LoadSceneCommand.h"
#include "LabMoveCommand.h"
#include "ChangeScoreCommand.h"
#include "DamageCommand.h"
#include "ScoreDisplay.h"

LabScene::LabScene(std::string name, std::string inputMapName)
	: Scene(std::move(name), std::move(inputMapName))
{
}

void LabScene::Load()
{
	using namespace dae;

	auto backgroundTex = ResourceManager::GetInstance().LoadTexture("background.tga");
	auto& backGround = CreateGameObject({});
	backGround.AddComponent<TextureComponent>(std::move(backgroundTex));

	auto logoTex = ResourceManager::GetInstance().LoadTexture("logo.tga");
	auto& logo = CreateGameObject();
	const auto pTextureComp = logo.AddComponent<TextureComponent>(std::move(logoTex));
	const auto textureSize = pTextureComp->GetTexture()->GetSize();
	logo.GetTransform()->SetLocalPosition(640 / 2.f - textureSize.x / 2.f, 480 / 2.f - textureSize.y / 2.f);

	auto fontBig = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto& title = CreateGameObject();
	title.AddComponent<TextComponent>("Programming 4 Assignment", std::move(fontBig));
	title.GetTransform()->SetLocalPosition(80, 40);

	{
		auto fontSmall = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
		auto& fpsCounter = CreateGameObject();
		fpsCounter.AddComponent<FPSCounter>();
		fpsCounter.AddComponent<TextComponent>("00", std::move(fontSmall), glm::u8vec4{ 255,255,0,255 });
		fpsCounter.GetTransform()->SetLocalPosition(0, 0);
	}

	auto characterOne = ResourceManager::GetInstance().LoadTexture("1.png");
	auto characterTwo = ResourceManager::GetInstance().LoadTexture("2.png");
	auto characterThree = ResourceManager::GetInstance().LoadTexture("3.png");

	auto& pengo = CreateGameObject();
	pengo.SetTag("Pengo");
	{
		const auto textureComp = pengo.AddComponent<TextureComponent>(std::move(characterOne));
		textureComp->SetRenderOffset(8, 8);
		pengo.GetTransform()->SetLocalPosition(640 / 2.f + 20, 480 / 2.f + 20);
		const auto collider = pengo.AddComponent<ColliderComponent>(pengo.GetTransform()->GetWorldPosition() - glm::vec2{ 8, 8 }, glm::vec2{ 16,16 });
		collider->EnableDrawDebug(true);
		pengo.AddComponent<Player>();
	}

	auto& child = pengo.CreateGameObject();
	const auto textureComp1 = child.AddComponent<TextureComponent>(std::move(characterTwo));
	textureComp1->SetRenderOffset(8, 8);
	child.GetTransform()->SetLocalPosition(20, 20);
	child.AddComponent<Rotator>(glm::vec2{ 0,0 }, 10.f);

	auto& snoBee = CreateGameObject();
	snoBee.SetTag("Sno-Bee");
	{
		const auto textureComp2 = snoBee.AddComponent<TextureComponent>(std::move(characterThree));
		textureComp2->SetRenderOffset(8, 8);
		snoBee.GetTransform()->SetLocalPosition(640 / 2.f + 50, 480 / 2.f + 20);
		const auto collider = snoBee.AddComponent<ColliderComponent>(snoBee.GetTransform()->GetWorldPosition() - glm::vec2{ 8, 8 }, glm::vec2{ 16,16 });
		collider->EnableDrawDebug(true);
		snoBee.AddComponent<Player>()->SetEnemy(pengo.GetComponent<ColliderComponent>());

		pengo.GetComponent<Player>()->SetEnemy(collider);
	}

	{
		// Controls
		auto& gamePadControls = CreateGameObject();
		{
			auto fontSmall = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
			gamePadControls.AddComponent<TextComponent>("Use the D-Pad to move Sno-Bee, Kill Pengo for points, press triangle/y to die", std::move(fontSmall), glm::u8vec4{ 255,255,255,255 });
			gamePadControls.GetTransform()->SetLocalPosition(2, 100);
		}
		// Lives Display
		{
			auto fontSmall = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
			auto& livesDisplay = gamePadControls.CreateGameObject();
			livesDisplay.AddComponent<LivesDisplay>()->SetLinkedPlayer(snoBee.GetComponent<Player>());
			livesDisplay.AddComponent<TextComponent>("test", std::move(fontSmall), glm::u8vec4{ 255,255,255,255 });
			livesDisplay.GetTransform()->SetLocalPosition(0, 25);
		}
		// Score Display
		{
			auto fontSmall = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
			auto& livesDisplay = gamePadControls.CreateGameObject();
			livesDisplay.AddComponent<ScoreDisplay>()->SetLinkedPlayer(snoBee.GetComponent<Player>());
			livesDisplay.AddComponent<TextComponent>("test", std::move(fontSmall), glm::u8vec4{ 255,255,255,255 });
			livesDisplay.GetTransform()->SetLocalPosition(0, 50);
		}
		// Controls
		auto& keyboardControls = CreateGameObject();
		{
			auto fontSmall = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
			keyboardControls.AddComponent<TextComponent>("Use WASD to move Pengo, press 1 for points, run into sno-bee to die", std::move(fontSmall), glm::u8vec4{ 255,255,255,255 });
			keyboardControls.GetTransform()->SetLocalPosition(2, 200);
		}
		// Lives Display
		{
			auto fontSmall = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
			auto& livesDisplay = keyboardControls.CreateGameObject();
			livesDisplay.AddComponent<LivesDisplay>()->SetLinkedPlayer(pengo.GetComponent<Player>());
			livesDisplay.AddComponent<TextComponent>("test", std::move(fontSmall), glm::u8vec4{ 255,255,255,255 });
			livesDisplay.GetTransform()->SetLocalPosition(0, 25);
		}
		// Score Display
		{
			auto fontSmall = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
			auto& livesDisplay = keyboardControls.CreateGameObject();
			livesDisplay.AddComponent<ScoreDisplay>()->SetLinkedPlayer(pengo.GetComponent<Player>());
			livesDisplay.AddComponent<TextComponent>("test", std::move(fontSmall), glm::u8vec4{ 255,255,255,255 });
			livesDisplay.GetTransform()->SetLocalPosition(0, 50);
		}
	}

	auto& input = InputManager::GetInstance();
	input.EnableGamePadInput(true);
	const auto id = input.RegisterGamePad();
	const auto map = input.AddInputMap("test");

	input.SetInputMapActive("test");
	map->AddKeyboardAction<LabMoveCommand>(0, KeyState::keyPressed, SDL_SCANCODE_W, &pengo, glm::ivec2{ 0,-1 }, 25);
	map->AddKeyboardAction<LabMoveCommand>(1, KeyState::keyPressed, SDL_SCANCODE_A, &pengo, glm::ivec2{ -1,0 }, 25);
	map->AddKeyboardAction<LabMoveCommand>(2, KeyState::keyPressed, SDL_SCANCODE_S, &pengo, glm::ivec2{ 0,1 }, 25);
	map->AddKeyboardAction<LabMoveCommand>(3, KeyState::keyPressed, SDL_SCANCODE_D, &pengo, glm::ivec2{ 1,0 }, 25);
	map->AddKeyboardAction<LoadSceneCommand>(4, KeyState::keyDown, SDL_SCANCODE_RETURN, "secondScene");
	map->AddKeyboardAction<ChangeScoreCommand>(5, KeyState::keyDown, SDL_SCANCODE_1, &pengo, 100);

	map->AddGamePadAction<LabMoveCommand>(id, 1, KeyState::keyPressed, GamePad::Button::dPadUp, &snoBee, glm::ivec2{ 0,-1 }, 50);
	map->AddGamePadAction<LabMoveCommand>(id, 2, KeyState::keyPressed, GamePad::Button::dPadLeft, &snoBee, glm::ivec2{ -1,0 }, 50);
	map->AddGamePadAction<LabMoveCommand>(id, 3, KeyState::keyPressed, GamePad::Button::dPadDown, &snoBee, glm::ivec2{ 0,1 }, 50);
	map->AddGamePadAction<LabMoveCommand>(id, 4, KeyState::keyPressed, GamePad::Button::dPadRight, &snoBee, glm::ivec2{ 1,0 }, 50);
	map->AddGamePadAction<DamageCommand>(id, 5, KeyState::keyUp, GamePad::Button::buttonUp, &snoBee);
}
