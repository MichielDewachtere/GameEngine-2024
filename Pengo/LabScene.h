#ifndef LABSCENE_H
#define LABSCENE_H

#include <Scene.h>

class LabScene final : public dae::Scene
{
public:
	explicit LabScene(std::string name, std::string inputMapName);
	virtual ~LabScene() override = default;

	LabScene(const LabScene& other) = delete;
	LabScene& operator=(const LabScene& rhs) = delete;
	LabScene(LabScene&& other) = delete;
	LabScene& operator=(LabScene&& rhs) = delete;

	virtual void Load() override;

private:
	
};

#endif // LABSCENE_H