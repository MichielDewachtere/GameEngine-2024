#ifndef LEVEL_H
#define LEVEL_H

#include <Scene.h>

class Level final : public dae::Scene
{
public:
	explicit Level(std::string level, std::string inputMap, bool debug = false);
	~Level() override = default;

	Level(const Level& other) = delete;
	Level& operator=(const Level& rhs) = delete;
	Level(Level&& other) = delete;
	Level& operator=(Level&& rhs) = delete;

	virtual void Load() override;

private:
	bool m_Debug;
};

#endif // LEVEL_H