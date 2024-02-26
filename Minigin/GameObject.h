#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Transform.h"

namespace dae
{
	class Texture2D;

	class GameObject final
	{
	public:
		explicit GameObject(std::string tag = "");
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// TODO: implement start
		void Start();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;

		void Destroy();
		bool IsEnabled() const { return m_IsEnabled && m_IsMarkedForDestroy == false; }

		void SetTag(std::string tag) { m_Tag = std::move(tag); }

		Transform* GetTransform() const { return m_pTransform.get(); }

		/**
		* @brief Adds a component to the GameObject.
		* @tparam T Type of the component to add.
		* @tparam Args Additional arguments for component construction.
		* @param args Additional arguments forwarded to the component constructor.
		* @return Pointer to the added component.
		*/
		template<typename T, typename... Args>
		// TODO: ask this
		// requires std::is_base_of_v<Component, T>
		T* AddComponent(Args... args);
		/**
		* @brief Gets a component of the GameObject.
		* @tparam T Type of the component to retrieve.
		* @return Pointer to the requested component, or nullptr if not found.
		*/
		template<typename T>
		T* GetComponent();
		/**
		 * @brief Removes a component from the GameObject.
		 * @tparam T Type of the component to remove.
		 * @return True if the component was removed successfully, false otherwise.
		 */
		template<typename T>
		bool RemoveComponent();
		/**
		 * @brief Checks if the GameObject has a specific component.
		 * @tparam T Type of the component to check.
		 * @return True if the GameObject has the component, false otherwise.
		 */
		template<typename T>
		bool HasComponent() const;

	private:
		UINT m_Id;
		std::string m_Tag;
		bool m_IsEnabled{ true }, m_IsMarkedForDestroy{ false };
		std::unique_ptr<Transform> m_pTransform{ nullptr };

		std::vector<std::unique_ptr<Component>> m_ComponentPtrs{};

		//template<typename T>
		//std::vector<std::unique_ptr<Component>>::iterator GetComponentIterator();
		template<typename T>
		bool IsTransform() const { return std::is_same_v<T, Transform>; }

		static inline UINT m_IdCounter = 0;
	};

	template <typename T, typename ... Args>
	T* GameObject::AddComponent(Args... args)
	{
		if (HasComponent<T>())
		{
			Logger::LogError({ "This game object already has a component of this type" });
			throw std::runtime_error("This game object already has a component of this type");
		}

		std::unique_ptr<T> pComponent = std::make_unique<T>(this, std::forward<Args>(args)...);
		T* rawPtr = pComponent.get();
		m_ComponentPtrs.emplace_back(std::move(pComponent));

		return rawPtr;
	}

	template <typename T>
	T* GameObject::GetComponent()
	{
		if (IsTransform<T>())
			return dynamic_cast<T*>(m_pTransform.get());

		const auto it = std::find_if(m_ComponentPtrs.begin(), m_ComponentPtrs.end(), [](const auto& c)
			{
				return dynamic_cast<T*>(c.get()) != nullptr;
			});

		if (it != m_ComponentPtrs.end())
		{
			return dynamic_cast<T*>(it->get());
		}

		Logger::LogError({"This game object has no component of this type"});
		return nullptr;
	}

	template <typename T>
	bool GameObject::RemoveComponent()
	{
		if (IsTransform<T>())
		{
			Logger::LogWarning({ "The transform component can not be deleted" });
			return false;
		}

		const auto it = std::find_if(m_ComponentPtrs.begin(), m_ComponentPtrs.end(), [](const auto& c)
			{
				return dynamic_cast<T*>(c.get()) != nullptr;
			});

		if (it != m_ComponentPtrs.end())
		{
			std::erase(m_ComponentPtrs, it);
			return true;
		}

		Logger::LogError({ "This game object has no component of this type" });
		return false;
	}

	template <typename T>
	bool GameObject::HasComponent() const
	{
		if constexpr (std::is_base_of_v<Component, T> == false)
		{
			Logger::LogError({ "T must derive from Component" });
			return false;
		}

		if (m_ComponentPtrs.empty())
			return false;

		if (IsTransform<T>())
			return true;

		const auto it = std::find_if(m_ComponentPtrs.begin(), m_ComponentPtrs.end(), [](const auto& c)
			{
				// TODO: Find out why this doesnt work
				//return std::is_same_v<T, decltype(c)>;
				return dynamic_cast<T*>(c.get()) != nullptr;
			});

		if (it == m_ComponentPtrs.end())
		{
			return false;
		}

		return true;
	}

	//template <typename T>
	//std::vector<std::unique_ptr<Component>>::iterator GameObject::GetComponentIterator()
	//{
	//	// ReSharper disable once CppEntityUsedOnlyInUnevaluatedContext
	//	const auto it = std::find_if(m_ComponentPtrs.begin(), m_ComponentPtrs.end(), [](const auto& c)
	//		{
	//			return std::is_same_v<T, decltype(*c)>;
	//		});

	//	return it;
	//}
}

#endif // GAMEOBJECT_H