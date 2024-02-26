#ifndef COMPONENT_H
#define COMPONENT_H

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		explicit Component(GameObject* pOwner);
		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component& operator=(const Component& rhs) = delete;
		Component(Component&& other) = delete;
		Component& operator=(Component&& rhs) = delete;

		virtual void Start() {}

		virtual void FixedUpdate() {}
		virtual void Update() {}
		virtual void LateUpdate() {}

		// This is for ImGui
		//virtual void OnGui() {}

		GameObject* GetOwner() const { return m_pOwner; }

	private:
		GameObject* m_pOwner;
	};
}

#endif // COMPONENT_H