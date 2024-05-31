#ifndef ICEBLOCK_H
#define ICEBLOCK_H

#include <Component.h>
#include <Observer.h>

#include "Player.h"
#include "PlayerManager.h"

namespace real
{
	class SpriteComponent;
}

enum class GameEvents : char;
enum class Direction : char;
class Move;

class IceBlock final
	: public real::Component
	, public real::Observer<GameEvents>
{
public:
	explicit IceBlock(real::GameObject* pOwner, bool hidesEgg, ECharacterColors color);
	virtual ~IceBlock() override;

	IceBlock(const IceBlock& other) = delete;
	IceBlock& operator=(const IceBlock& rhs) = delete;
	IceBlock(IceBlock&& other) = delete;
	IceBlock& operator=(IceBlock&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void HandleEvent(GameEvents) override;
	void OnSubjectDestroy() override {}

	void Break(PlayerNumber breakedBy = PlayerNumber::none);

	bool HidesEgg() const { return m_HidesEgg; }

private:
	ECharacterColors m_Color;
	bool m_HidesEgg{ false }, m_Break{ false }, m_StartAnimation{ true };
	real::SpriteComponent* m_pSpriteComponent{ nullptr };
	PlayerNumber m_BreakedBy{};
};

#endif // ICEBLOCK_H