#include "HighScoreDisplay.h"

#include <fstream>
#include <sstream>
#include <string>

#include <TextComponent.h>
#include <GameObject.h>
#include <Logger.h>

#include "PlayerManager.h"

HighScoreDisplay::HighScoreDisplay(real::GameObject* pOwner)
	: Component(pOwner)
{
}

void HighScoreDisplay::Start()
{
    const auto i = PlayerManager::GetInstance().GetAmountOfPlayers();
	m_HighScore = LoadHighScore(i < 2 ? true : false);

    m_pTextComponent = GetOwner()->GetComponent<real::TextComponent>();
    m_pTextComponent->SetText(std::to_string(m_HighScore));
}

void HighScoreDisplay::CheckForHighScore(int score) const
{
	if (score > m_HighScore)
	{
		m_HighScore = score;
        m_pTextComponent->SetText(std::to_string(m_HighScore));
	}
}

bool HighScoreDisplay::IsTopFive(int score)
{
    return score > m_TopFiveScore;
}


int HighScoreDisplay::LoadHighScore(const bool singlePlayer) const
{
    std::string filePath = "../data/high_scores.txt";
    std::ifstream file(filePath);
    int highScore = m_HighScore;

    if (file.is_open())
    {
	    std::string line;
	    while (getline(file, line))
        {
            std::stringstream ss(line);
            std::string token;

            // Tokenize the line using ':' as delimiter
            getline(ss, token, ':'); // Get the first token
            if (token != (singlePlayer ? "1" : "2"))
                continue;

            // Tokenize the line using ':' as delimiter
            while (getline(ss, token, ':'))
            {
                if (token == "1")
                {
                    getline(ss, token, ':'); // Skip the second token
                    getline(ss, token, ':'); // Get the third token
                    const int score = stoi(token);

                    if (score > highScore)
                        highScore = score;
                }
                else if (token == "5")
                {
                    getline(ss, token, ':'); // Skip the second token
                    getline(ss, token, ':'); // Get the third token
                    m_TopFiveScore = stoi(token);
                }
            }
        }
        file.close();
    }
    else
        real::Logger::LogWarning({ "Unable to open high scores using file : {}" }, filePath);

    return highScore;
}
