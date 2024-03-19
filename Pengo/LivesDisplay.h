#ifndef LIVESDISPLAY_H
#define LIVESDISPLAY_H

#include <stdint.h>

#include <Component.h>
#include <Observer.h>

namespace dae
{
	class TextComponent;
}

class Player;

class LivesDisplay final
	: public dae::Component
	, public dae::Observer<uint8_t>
{
public:
	explicit LivesDisplay(dae::GameObject* pOwner);
	~LivesDisplay() override;

	LivesDisplay(const LivesDisplay& other) = delete;
	LivesDisplay& operator=(const LivesDisplay& rhs) = delete;
	LivesDisplay(LivesDisplay&& other) = delete;
	LivesDisplay& operator=(LivesDisplay&& rhs) = delete;

	//virtual void Start() override;

	virtual void HandleEvent(unsigned char) override;
	virtual void OnSubjectDestroy() override;

	void SetLinkedPlayer(Player* pPlayer);

private:
	// Test code
	Player* m_pLinkedPlayer{ nullptr };
	dae::TextComponent* m_pTextComponent{ nullptr };
};

#endif // LIVESDISPLAY_H