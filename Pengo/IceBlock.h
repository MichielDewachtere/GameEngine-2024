#ifndef ICEBLOCK_H
#define ICEBLOCK_H

#include <Component.h>

namespace dae
{
	class SpriteComponent;
}

enum class Direction : char;
class Move;

class IceBlock final : public dae::Component
{
public:
	explicit IceBlock(dae::GameObject* pOwner, bool hidesEgg);
	virtual ~IceBlock() override = default;

	IceBlock(const IceBlock& other) = delete;
	IceBlock& operator=(const IceBlock& rhs) = delete;
	IceBlock(IceBlock&& other) = delete;
	IceBlock& operator=(IceBlock&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void Break();

private:
	bool m_HidesEgg{ false }, m_Break{ false }, m_StartAnimation{ true };
	dae::SpriteComponent* m_pSpriteComponent{ nullptr };
};

#endif // ICEBLOCK_H