#include "EnterName.h"

#include <GameObject.h>
#include <TextComponent.h>
#include <TextureComponent.h>
#include <Colors.h>
#include <ranges>
#include <ResourceManager.h>
#include <InputManager.h>

#include "GameInfo.h"
#include "PlayerManager.h"
#include "StartGameCommand.h"
#include "StartScreen.h"

EnterName::EnterName(real::GameObject* pOwner)
	: Component(pOwner)
	, m_LinkedPlayer(0)
{
	m_Name.fill({ 'A', nullptr });
}

void EnterName::Start()
{
	for (size_t i{ 0 }; i < static_cast<size_t>(max_amount_of_characters); ++i)
	{
		AddTextComponent(i);
	}
	m_Name[m_CurrentPosition].second->SetColor(real::Colors::yellow);
}

void EnterName::EnterCharacter(int controllerId)
{
	if (m_CurrentPosition >= static_cast<int>(m_Name.size()))
		return;

	m_Name[m_CurrentPosition].first = m_CurrentCharacter;
	m_Name[m_CurrentPosition].second->SetColor(real::Colors::white);
	++m_CurrentPosition;

	if (m_CurrentPosition >= static_cast<int>(m_Name.size()))
	{
		std::string s;
		for (const auto& c : m_Name | std::views::keys)
		{
			s.push_back(c);
		}

		PlayerManager::GetInstance().SetNameOfPlayer(m_LinkedPlayer, s);

		const auto map = real::InputManager::GetInstance().GetActiveInputMap();
		if (controllerId == -1)
		{
			map->RemoveKeyboardAction(InputCommands::name_character_confirm);
			map->RemoveKeyboardAction(InputCommands::name_character_down);
			map->RemoveKeyboardAction(InputCommands::name_character_up);
		}
		else
		{
			map->RemoveGamePadAction(InputCommands::name_character_confirm, controllerId);
			map->RemoveGamePadAction(InputCommands::name_character_down, controllerId);
			map->RemoveGamePadAction(InputCommands::name_character_up, controllerId);
		}

		GetOwner()->GetParent()->GetParent()->GetComponent<StartScreen>()->PlayerSelected();

		return;
	}

	m_Name[m_CurrentPosition].second->SetColor(real::Colors::yellow);
}

void EnterName::ChangeCharacter(bool up)
{
	if (m_CurrentPosition >= max_amount_of_characters)
		return;

	auto newChar = m_CurrentCharacter;
	if (up)
	{
		++newChar;
		if (newChar > highest_char)
			newChar = lowest_char;
	}
	else
	{
		--newChar;
		if (newChar < lowest_char)
			newChar = highest_char;
	}

	m_CurrentCharacter = newChar;
	m_Name[m_CurrentPosition].second->SetText({ m_CurrentCharacter });
}

void EnterName::AddTextComponent(const size_t id)
{
	constexpr float characterOffset = 24.f;
	constexpr float begin = 34.f;

	auto pFont = real::ResourceManager::GetInstance().LoadFont("joystix-monospace.otf", 24);

	auto& text = GetOwner()->CreateGameObject();
	text.GetTransform()->SetLocalPosition(static_cast<float>(id) * characterOffset - begin, 30);

	text.AddComponent<real::TextureComponent>();
	const auto textComp = text.AddComponent<real::TextComponent>();
	textComp->SetFont(std::move(pFont));
	textComp->SetText({ m_Name[id].first });

	m_Name[id].second = textComp;
}
