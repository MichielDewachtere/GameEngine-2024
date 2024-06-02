#include "StartMenu.h"

#include <ResourceManager.h>
#include <InputManager.h>
#include <TextComponent.h>
#include <TextureComponent.h>
#include <Locator.h>
#include <Colors.h>

#include "FlickerText.h"
#include "GameInfo.h"
#include "Macros.h"
#include "SelectMode.h"
#include "StartScreen.h"

StartMenu::StartMenu(std::string name, std::string inputMap, real::WindowSettings settings)
	: Scene(std::move(name), std::move(inputMap))
	, m_Settings(std::move(settings))
{
}

void StartMenu::Load()
{
	real::TransformInfo transformInfo{};
	transformInfo.position = glm::vec3{ static_cast<float>(m_Settings.width) / 2.f, 150, 0 };
	transformInfo.scale = glm::vec3{ PIXEL_SCALE };
	auto& startScreen = CreateGameObject(transformInfo, "start-screen");
	{
		real::TextureInfo info{};
		info.pTexture = real::ResourceManager::GetInstance().LoadTexture("textures/title.png");
		const auto size = info.pTexture->GetSize() * PIXEL_SCALE;
		info.offset = { size.x / 2, size.y / 2 };
		startScreen.AddComponent<real::TextureComponent>(std::move(info));
		startScreen.AddComponent<StartScreen>();
	}

	auto& mode = startScreen.CreateGameObject({ glm::vec3{0,150,0} }, "select-mode");
	{
		mode.AddComponent<real::TextureComponent>();

		real::TextInfo info{};
		info.text = "mode";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
		info.color = real::Colors::red;
		info.horizontalAlignment = real::HorizontalTextAlignment::center;
		mode.AddComponent<real::TextComponent>(std::move(info));

		mode.AddComponent<SelectMode>();
	}

	auto& start = startScreen.CreateGameObject({ glm::vec3{0,600,0} }, "start-button");
	{
		start.AddComponent<real::TextureComponent>();

		real::TextInfo info{};
		info.text = "-start-";
		info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), 64);
		info.color = real::Colors::grey;
		info.horizontalAlignment = real::HorizontalTextAlignment::center;
		start.AddComponent<real::TextComponent>(std::move(info));

		start.AddComponent<FlickerText>(real::Colors::yellow, 0.5f)->Disable();
	}
}