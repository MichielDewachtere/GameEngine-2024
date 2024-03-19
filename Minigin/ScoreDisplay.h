#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include "Component.h"
#include "Observer.h"

class Player;

namespace dae
{
	class TextComponent;
}

class ScoreDisplay final
	: public dae::Component
	, public dae::Observer<uint32_t>
{
public:
	explicit ScoreDisplay(dae::GameObject* pOwner);
	~ScoreDisplay() override;

	ScoreDisplay(const ScoreDisplay& other) = delete;
	ScoreDisplay& operator=(const ScoreDisplay& rhs) = delete;
	ScoreDisplay(ScoreDisplay&& other) = delete;
	ScoreDisplay& operator=(ScoreDisplay&& rhs) = delete;

	void HandleEvent(uint32_t) override;
	void OnSubjectDestroy() override;

	void SetLinkedPlayer(Player* pPlayer);

private:
	Player* m_pLinkedPlayer{ nullptr };
	dae::TextComponent* m_pTextComponent{ nullptr };
};

#endif // SCOREDISPLAY_H