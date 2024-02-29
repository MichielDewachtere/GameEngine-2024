#ifndef SCENE_H
#define SCENE_H

#include "GameObject.h"

namespace dae
{
	class Scene final
	{
	public:
		explicit Scene(std::string name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void FixedUpdate();
		void Update();
		void Render() const;

		const std::string& GetName() const { return m_Name; }

		GameObject& CreateGameObject(std::string tag = "");
		void AddGameObject(GameObject* pGo);
		void AddGameObject(std::unique_ptr<GameObject> pGo);
		GameObject* GetGameObject(UINT id) const;
		std::unique_ptr<GameObject> GetUniqueGameObject(GameObject* pGo);
		void Remove(GameObject* pGo);
		void RemoveAll();


		void Destroy();

	private:
		friend class GameObject;

		bool m_IsFirstFrame{ true }, m_DeleteGameObject{ false };
		std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_GameObjects{};

		static unsigned int m_IdCounter; 
	};

}

#endif // SCENE_H