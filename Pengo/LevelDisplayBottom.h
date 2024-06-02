#ifndef LEVELDISPLAYBOTTOM_H
#define LEVELDISPLAYBOTTOM_H

#include <Observer.h>
#include <Component.h>

namespace real
{
	class TextComponent;
	enum class SceneEvents : char;
	class Scene;
}

class LevelDisplayBottom final
	: public real::Component
	, public real::Observer<real::SceneEvents, real::Scene*>
{
public:
	explicit LevelDisplayBottom(real::GameObject* pOwner);
	virtual ~LevelDisplayBottom() override;

	LevelDisplayBottom(const LevelDisplayBottom& other) = delete;
	LevelDisplayBottom& operator=(const LevelDisplayBottom& rhs) = delete;
	LevelDisplayBottom(LevelDisplayBottom&& other) = delete;
	LevelDisplayBottom& operator=(LevelDisplayBottom&& rhs) = delete;

	void HandleEvent(real::SceneEvents, real::Scene*) override;
	void OnSubjectDestroy() override {}

	void Reset() const;

private:
	real::TextComponent* m_pTextComponent{ nullptr };

	void InitAct(int id) const;
	void SetActive(int amount) const;
};

#endif // LEVELDISPLAYBOTTOM_H