#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "Singleton.h"

namespace dae
{
	class GameObject;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Init() override;
		bool ProcessInput();

		// TODO: Delete this after week 2, this is for testing only
		UINT m_ParentId, m_ChildId;
	};

}

#endif // INPUTMANAGER_H