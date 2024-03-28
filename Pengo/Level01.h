#ifndef LEVEL01_H
#define LEVEL01_H

#include <Scene.h>

class Level01 final : public dae::Scene
{
public:
	explicit Level01();
	~Level01() override = default;

	Level01(const Level01& other) = delete;
	Level01& operator=(const Level01& rhs) = delete;
	Level01(Level01&& other) = delete;
	Level01& operator=(Level01&& rhs) = delete;

	virtual void Load() override;
};

#endif // LEVEL01_H