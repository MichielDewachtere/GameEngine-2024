#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "Component.h"

namespace dae
{
	// TODO:
	class SpriteComponent final : public Component
	{
	public:
		explicit SpriteComponent(GameObject* pOwner);
		virtual ~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& rhs) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& rhs) = delete;

	private:

	};
}

#endif // SPRITECOMPONENT_H