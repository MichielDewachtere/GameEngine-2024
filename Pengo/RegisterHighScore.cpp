#include "RegisterHighScore.h"

#include <Colors.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <TextComponent.h>
#include <TextureComponent.h>
#include <InputManager.h>

#include "Game.h"
#include "GameInfo.h"
#include "HandleNameCommand.h"
#include "HUD.h"
#include "LeaderBoard.h"
#include "Locator.h"
#include "PlayerManager.h"

RegisterHighScore::RegisterHighScore(real::GameObject* pOwner)
	: Component(pOwner)
{
}

void RegisterHighScore::Start()
{
    real::Locator::GetAudioSystem().Stop(Sounds::name_entry.channel);
    real::Locator::GetAudioSystem().Play(Sounds::name_entry);

	LeaderBoard::WriteCategories(GetOwner(), 50, real::Colors::green);
    WriteData();
}

void RegisterHighScore::WriteData() const
{
    constexpr float verticalOffset = 100;

    {
        auto& score = GetOwner()->CreateGameObject();
        score.GetTransform()->SetLocalPosition(LeaderBoard::score_offset, verticalOffset);
        score.AddComponent<real::TextureComponent>();

        real::TextInfo info{};
        info.text = std::to_string(HUD::GetInstance().GetTotalScore());
        info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
        info.color = real::Colors::white;
        info.horizontalAlignment = real::HorizontalTextAlignment::center;
		score.AddComponent<real::TextComponent>(std::move(info));
    }
    {
        auto& act = GetOwner()->CreateGameObject();
        act.GetTransform()->SetLocalPosition(LeaderBoard::act_offset, verticalOffset);
        act.AddComponent<real::TextureComponent>();

        real::TextInfo info{};
        info.text = std::to_string(Game::GetCurrentLevel());
        info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
        info.color = real::Colors::white;
        info.horizontalAlignment = real::HorizontalTextAlignment::center;
    	act.AddComponent<real::TextComponent>(std::move(info));
    }
    {
        auto& name = GetOwner()->CreateGameObject({}, "enter-name");
        name.GetTransform()->SetLocalPosition(LeaderBoard::name_offset, verticalOffset);
        name.AddComponent<EnterName>();

        AddCommands(&name);
    }
}

void RegisterHighScore::AddCommands(real::GameObject* enterName)
{
	const auto map = real::InputManager::GetInstance().GetActiveInputMap();
    for (const auto& p : PlayerManager::GetInstance().GetPlayers())
    {
        if (p.controllerId == UCHAR_MAX)
        {
            map->AddKeyboardAction<HandleNameCommand>(InputCommands::name_character_confirm, real::KeyState::keyUp,
                                                      SDL_SCANCODE_SPACE, enterName, true, true);
            map->AddKeyboardAction<HandleNameCommand>(InputCommands::name_character_up, real::KeyState::keyUp,
                                                      SDL_SCANCODE_UP, enterName, false, true);
            map->AddKeyboardAction<HandleNameCommand>(InputCommands::name_character_down, real::KeyState::keyUp,
                                                      SDL_SCANCODE_DOWN, enterName, false, false);
        }
        else
        {
            map->AddGamePadAction<HandleNameCommand>(p.controllerId, InputCommands::name_character_confirm,
                                                     real::KeyState::keyUp, real::GamePad::Button::buttonDown,
                                                     enterName, true, true);
            map->AddGamePadAction<HandleNameCommand>(p.controllerId, InputCommands::name_character_up,
                                                     real::KeyState::keyUp, real::GamePad::Button::dPadUp, enterName,
                                                     false, true);
            map->AddGamePadAction<HandleNameCommand>(p.controllerId, InputCommands::name_character_down,
                                                     real::KeyState::keyUp, real::GamePad::Button::dPadDown, enterName,
                                                     false, false);
        }
    }
}
