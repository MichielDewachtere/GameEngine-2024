#ifndef COMPONENT_H
#define COMPONENT_H

namespace real
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
		virtual void OnGui() {}

		virtual void Kill() {}

		GameObject* GetOwner() const { return m_pOwner; }

		void Disable() { m_IsActive = false; }
		void Enable() { m_IsActive = true; }
		bool IsActive() const { return m_IsActive; }

		void Destroy() { m_MarkedForDestroy = true; }
		bool IsMarkedForDestroy() const { return m_MarkedForDestroy; }

	private:
		GameObject* m_pOwner;
		bool m_IsActive{ true }, m_MarkedForDestroy{ false };
	};
}

#endif // COMPONENT_H