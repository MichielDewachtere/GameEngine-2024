#include "Level01.h"

#include "InputManager.h"
#include "LevelParser.h"
#include "PlayerManager.h"

Level01::Level01()
	: Scene("level01", "gameplay")
{
}

void Level01::Load()
{
	auto& input = dae::InputManager::GetInstance();
	input.AddInputMap("test");
	input.EnableGamePadInput(true);
	input.SetInputMapActive("test");


	PlayerManager::GetInstance().RegisterPlayer({ nullptr, true, 255 });

	const auto idx = input.RegisterGamePad();
	if (idx != UCHAR_MAX)
		PlayerManager::GetInstance().RegisterPlayer({ nullptr, false, idx });

	LevelParser::ParseLevel(this, "../data/levels/test_level.lvl", 5);
}
