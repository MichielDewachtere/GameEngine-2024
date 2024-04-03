#ifndef HUD_H
#define HUD_H

#include <memory>
#include <Singleton.h>

#include "Observer.h"

namespace dae
{
	class Scene;
	class GameObject;
	enum class SceneEvents : char;
}

enum class ScoreEvents : char;
class ScoreDisplay;

class HUD final
	: public dae::Singleton<HUD>
	, public dae::Observer<dae::SceneEvents, dae::Scene*>
{
public:
	virtual ~HUD() override;

	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& rhs) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(HUD&& rhs) = delete;

	virtual void Init() override;

	virtual void HandleEvent(dae::SceneEvents, dae::Scene* pScene) override;
	virtual void OnSubjectDestroy() override {}

	void AddScore(ScoreEvents event) const;

private:
	friend class Singleton<HUD>;
	explicit HUD() = default;

	uint32_t m_HudId{};
	std::unique_ptr<dae::GameObject> m_pUniqueHud{};
	//dae::GameObject* m_pRawHud{};
	ScoreDisplay* m_pScoreDisplayPlayerOne{ nullptr };

	void InitHud();
	void InitScoreDisplay();
	//void InitHighScoreDisplay();
	//void InitLivesDisplay();
	//void InitEnemyDisplay();
	//void InitLevelDisplayTop();
	//void InitLevelDisplayBottom();
};

#endif // HUD_H