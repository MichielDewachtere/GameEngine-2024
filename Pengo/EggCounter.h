#ifndef EGGCOUNTER_H
#define EGGCOUNTER_H

#include <Component.h>
#include <Observer.h>
#include <vector>

namespace real
{
	class Scene;
	enum class SceneEvents : char;
}

class EggCounter final
	: public real::Component
	, public real::Observer<real::SceneEvents, real::Scene*>
	, public real::Observer<>
{
public:
	explicit EggCounter(real::GameObject* pOwner);
	virtual ~EggCounter() override;

	EggCounter(const EggCounter& other) = delete;
	EggCounter& operator=(const EggCounter& rhs) = delete;
	EggCounter(EggCounter&& other) = delete;
	EggCounter& operator=(EggCounter&& rhs) = delete;

	virtual void Start() override;

	virtual void HandleEvent(real::SceneEvents, real::Scene*) override;
	virtual void HandleEvent() override;

	void OnSubjectDestroy() override {}

private:
	void InitEgg(int id) const;
	std::vector<uint32_t> m_AlreadyDestroyed;
};

#endif // EGGCOUNTER_H