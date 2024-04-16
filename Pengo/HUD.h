#ifndef HUD_H
#define HUD_H

#include <memory>
#include <Singleton.h>

#include "Observer.h"

class HealthDisplay;

namespace real
{
	class Scene;
	class GameObject;
	enum class SceneEvents : char;
}

enum class ScoreEvents : char;
enum class PlayerNumber : char;
class ScoreDisplay;

class HUD final
	: public real::Singleton<HUD>
	, public real::Observer<real::SceneEvents, real::Scene*>
{
public:
	virtual ~HUD() override;

	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& rhs) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(HUD&& rhs) = delete;

	virtual void Init() override;

	virtual void HandleEvent(real::SceneEvents, real::Scene* pScene) override;
	virtual void OnSubjectDestroy() override {}

	void AddScore(ScoreEvents event, PlayerNumber p1) const;

	void AddLife() const;
	void RemoveLife() const;

private:
	friend class Singleton<HUD>;
	explicit HUD() = default;

	uint32_t m_HudId{};
	std::unique_ptr<real::GameObject> m_pUniqueHud{};
	ScoreDisplay * m_pScoreDisplayPlayerOne{ nullptr }, * m_pScoreDisplayPlayerTwo{ nullptr };
	HealthDisplay* m_pHealthDisplay{ nullptr };

	void InitHud();
	void InitScoreDisplay(PlayerNumber p);
	void InitHighScoreDisplay() const;
	void InitLivesDisplay();
	//void InitEnemyDisplay();
	//void InitLevelDisplayTop();
	//void InitLevelDisplayBottom();
};

#endif // HUD_H