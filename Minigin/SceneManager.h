#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Singleton.h"

namespace dae
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager() override;
		SceneManager(const SceneManager& other) = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) = delete;
		SceneManager& operator=(SceneManager&& other) = delete;

		Scene& CreateScene(std::string name);
		//Scene& AddScene(std::string name);
		//bool HasScene(const std::string& name);

		void FixedUpdate();
		void Update();
		void Render() const;

		void Destroy();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		//std::vector<std::unique_ptr<Scene>> m_ScenePtrs;
		std::vector<Scene*> m_ScenePtrs;
		std::string m_CreatingScene{};
	};
}

#endif // SCENEMANAGER_H