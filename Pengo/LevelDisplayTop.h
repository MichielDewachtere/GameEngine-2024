#ifndef LEVELDISPLAYTOP_H
#define LEVELDISPLAYTOP_H

#include <Observer.h>
#include <Component.h>

namespace real
{
	class Scene;
	enum class SceneEvents : char;
}

class LevelDisplayTop final
	: public real::Component
	, public real::Observer<real::SceneEvents, real::Scene*>
{
public:
	explicit LevelDisplayTop(real::GameObject* pOwner);
	virtual ~LevelDisplayTop() override;

	LevelDisplayTop(const LevelDisplayTop& other) = delete;
	LevelDisplayTop& operator=(const LevelDisplayTop& rhs) = delete;
	LevelDisplayTop(LevelDisplayTop&& other) = delete;
	LevelDisplayTop& operator=(LevelDisplayTop&& rhs) = delete;

	void HandleEvent(real::SceneEvents, real::Scene*) override;
	void OnSubjectDestroy() override {}

private:
	
};

#endif // LEVELDISPLAYTOP_H