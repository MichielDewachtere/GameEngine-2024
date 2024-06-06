#include "LeaderBoard.h"

#include <fstream>
#include <sstream>
#include <algorithm>

#include <Logger.h>
#include <GameObject.h>
#include <SceneManager.h>
#include <TextComponent.h>
#include <TextureComponent.h>
#include <ResourceManager.h>
#include <Colors.h>

#include "Game.h"
#include "GameInfo.h"
#include "HUD.h"
#include "PlayerManager.h"

LeaderBoard::LeaderBoard(real::GameObject* pOwner)
	: Component(pOwner)
{
}

LeaderBoard::~LeaderBoard() = default;

void LeaderBoard::Start()
{
	const auto i = PlayerManager::GetInstance().GetAmountOfPlayers();
    LoadLeaderBoard(i < 2 ? true : false);
    InsertPlayerScore(HUD::GetInstance().GetTotalScore());

    WriteCategories(GetOwner(), 50, real::Colors::pink);

    for (const auto& data : m_LeaderBoard)
        WriteData(data);

	const auto component = real::SceneManager::GetInstance().GetActiveScene().FindGameObjectsWithTag("enter-name").front()->GetComponent<EnterName>();
    component->nameEntered.AddObserver(this);
    component->characterEntered.AddObserver(this);
}

void LeaderBoard::WriteCategories(real::GameObject* pOwner, float localYPos, const glm::u8vec4& color)
{
	auto& categories = pOwner->CreateGameObject();
    categories.GetTransform()->SetLocalPosition(0, localYPos);

	{
        auto& score = categories.CreateGameObject();
        score.GetTransform()->SetLocalPosition(score_offset, 0);
		score.AddComponent<real::TextureComponent>();

        real::TextInfo info{};
        info.text = "score";
        info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
        info.color = color;
        info.horizontalAlignment = real::HorizontalTextAlignment::center;
        score.AddComponent<real::TextComponent>(std::move(info));
	}
	{
        auto& act = categories.CreateGameObject();
        act.GetTransform()->SetLocalPosition(act_offset, 0);
		act.AddComponent<real::TextureComponent>();

        real::TextInfo info{};
        info.text = "act";
        info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
        info.color = color;
        info.horizontalAlignment = real::HorizontalTextAlignment::center;
        act.AddComponent<real::TextComponent>(std::move(info));
	}
	{
		auto& name = categories.CreateGameObject();
        name.GetTransform()->SetLocalPosition(name_offset, 0);
		name.AddComponent<real::TextureComponent>();

        real::TextInfo info{};
        info.text = "name";
        info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
        info.color = color;
        info.horizontalAlignment = real::HorizontalTextAlignment::center;
        name.AddComponent<real::TextComponent>(std::move(info));
	}
}

void LeaderBoard::WriteData(const Data& data)
{
    constexpr float verticalOffset = 20 * PIXEL_SCALE;
    const float totalOffset = 40 + static_cast<float>(data.place) * verticalOffset;

    auto& categories = GetOwner()->CreateGameObject();
    categories.GetTransform()->SetLocalPosition(0, totalOffset);

    glm::u8vec4 color = real::Colors::cyan;
    if (data.name.empty())
        color = real::Colors::yellow;

    {
        auto& place = categories.CreateGameObject();
        place.GetTransform()->SetLocalPosition(place_offset, 0);
        place.AddComponent<real::TextureComponent>();

        real::TextInfo info{};
        info.text = m_PlaceToString[data.place];
        info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
        info.color = color;
        info.horizontalAlignment = real::HorizontalTextAlignment::center;
        place.AddComponent<real::TextComponent>(std::move(info));
    }
    {
        auto& score = categories.CreateGameObject();
        score.GetTransform()->SetLocalPosition(score_offset, 0);
        score.AddComponent<real::TextureComponent>();

        real::TextInfo info{};
        info.text = std::to_string(data.score);
        info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
        info.color = color;
        info.horizontalAlignment = real::HorizontalTextAlignment::center;
        score.AddComponent<real::TextComponent>(std::move(info));
    }
    {
        auto& act = categories.CreateGameObject();
        act.GetTransform()->SetLocalPosition(act_offset, 0);
        act.AddComponent<real::TextureComponent>();

        real::TextInfo info{};
        info.text = std::to_string(data.act);
        info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
        info.color = color;
        info.horizontalAlignment = real::HorizontalTextAlignment::center;
        act.AddComponent<real::TextComponent>(std::move(info));
    }
    {
        auto& name = categories.CreateGameObject();
        name.GetTransform()->SetLocalPosition(name_offset, 0);
        if (data.name.empty() == false)
        {
            name.AddComponent<real::TextureComponent>();

            real::TextInfo info{};
            info.text = data.name;
            info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
            info.color = color;
            info.horizontalAlignment = real::HorizontalTextAlignment::center;
            name.AddComponent<real::TextComponent>(std::move(info));
        }
        else
        {
            m_PLayerNameId = name.GetId();
        }
    }
}

void LeaderBoard::HandleEvent(EnterName::Events event, char character)
{
    if (event == EnterName::Events::characterEntered)
    {
        if (m_pPlayerName == nullptr)
        {
			const auto name = GetOwner()->GetChild(m_PLayerNameId);
            name->AddComponent<real::TextureComponent>();

            real::TextInfo info{};
            info.text = std::string{ character };
            info.pFont = real::ResourceManager::GetInstance().LoadFont(std::string(FONT_PATH), FONT_SIZE);
            info.color = real::Colors::yellow;
            info.horizontalAlignment = real::HorizontalTextAlignment::center;
            m_pPlayerName = name->AddComponent<real::TextComponent>(std::move(info));

        	return;
        }

        auto s = m_pPlayerName->GetText();
        s.push_back(character);
        m_pPlayerName->SetText(s);
    }
}

void LeaderBoard::HandleEvent(EnterName::Events event, const std::string& name)
{
    if (event == EnterName::Events::nameConfirmed)
    {
    	for (auto& p : m_LeaderBoard)
        {
            if (p.name.empty())
                p.name = name;
        }

        const auto i = PlayerManager::GetInstance().GetAmountOfPlayers();
        SaveLeaderBoard(i < 2 ? true : false);
        real::SceneManager::GetInstance().SetSceneActive(Scenes::game_over_menu, 1.5f);
    }
}

void LeaderBoard::OnSubjectDestroy() {}

void LeaderBoard::LoadLeaderBoard(const bool singlePlayer)
{
    std::string filePath = "../data/high_scores.txt";
    std::ifstream file(filePath);

    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            m_File += line;
            m_File += '\n';

            std::stringstream ss(line);
            std::string token;

            // Tokenize the line using ':' as delimiter
            getline(ss, token, ':'); // Get the first token
            if (token != (singlePlayer ? "1" : Game::GetIsPvP() ? "3" : "2"))
                continue;

            Data data;
            getline(ss, token, ':');
            data.place = std::stoi(token);
            getline(ss, token, ':');
            data.name = token;
            getline(ss, token, ':');
            data.score = std::stoi(token);
            getline(ss, token, ':');
            data.act = std::stoi(token);
            //data.act = Game::GetCurrentLevel();

            m_LeaderBoard[data.place - 1] = data;
        }
        file.close();
    }
    else
        real::Logger::LogWarning({ "Unable to open high scores using file : {}" }, filePath);
}

void LeaderBoard::InsertPlayerScore(int score)
{
	const Data playerData{ 0, score, Game::GetCurrentLevel(), "" };
    m_LeaderBoard.back() = playerData;

    std::ranges::sort(m_LeaderBoard, [](const Data& data1, const Data& data2)
        {
            return data1.score > data2.score;
        });

    for (int i = 0; i < static_cast<int>(m_LeaderBoard.size()); ++i)
        m_LeaderBoard[i].place = i + 1;
}

void LeaderBoard::SaveLeaderBoard(bool singlePlayer) const
{
	std::istringstream file(m_File);
    std::string line, newFile;

	while (getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;

        // Tokenize the line using ':' as delimiter
        getline(ss, token, ':'); // Get the first token
        if (token != (singlePlayer ? "1" : "2"))
        {
            newFile += line + '\n';
	        continue;
        }

        newFile += token;

        getline(ss, token, ':');
        const auto place = std::stoi(token);
        newFile += ':' + token;

        Data data = m_LeaderBoard[place - 1];

        getline(ss, token, ':');
        newFile += ':' + data.name;

        getline(ss, token, ':');
        newFile += ':' + std::to_string(data.score);

        getline(ss, token, ':');
        newFile += ':' + std::to_string(data.act);

		newFile += '\n';
    }

    // Write newFile data to the original file
    std::ofstream outFile("../data/high_scores.txt");
    if (outFile.is_open())
        outFile << newFile;
}
