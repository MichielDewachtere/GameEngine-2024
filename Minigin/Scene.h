#ifndef SCENE_H
#define SCENE_H

#include "SceneManager.h"
#include "GameObject.h"

namespace dae
{
	//class GameObject;

	class Scene final
	{
	public:
		~Scene();
		Scene(const Scene& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void FixedUpdate();
		void Update();
		void Render() const;

		const std::string& GetName() const { return m_Name; }

		GameObject& CreateGameObject();
		//void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void Destroy();

	private:
		explicit Scene(std::string name);
		friend Scene& SceneManager::CreateScene(std::string name);

		std::string m_Name;
		std::vector<std::unique_ptr<GameObject>> m_GameObjects{};

		static unsigned int m_IdCounter; 
	};

}

#endif // SCENE_H