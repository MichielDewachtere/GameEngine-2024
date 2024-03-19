#ifndef TESTSECONDSCENE_H
#define TESTSECONDSCENE_H

#include "Scene.h"

class TestSecondScene final : public dae::Scene
{
public:
	explicit TestSecondScene(std::string name, std::string inputMap);
	virtual ~TestSecondScene() override = default;

	TestSecondScene(const TestSecondScene& other) = delete;
	TestSecondScene& operator=(const TestSecondScene& rhs) = delete;
	TestSecondScene(TestSecondScene&& other) = delete;
	TestSecondScene& operator=(TestSecondScene&& rhs) = delete;

	virtual void Load() override;

private:
	
};

#endif // TESTSECONDSCENE_H