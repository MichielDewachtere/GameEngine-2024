#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Singleton.h"
#include "Scene.h"

namespace dae
{
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
		void OnGui();

		void SetSceneActive(Scene& scene) { m_pActiveScene = &scene; }
		Scene& GetActiveScene() const { return *m_pActiveScene; }

		void Destroy();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::unique_ptr<Scene>> m_ScenePtrs;
		Scene* m_pActiveScene;
		std::string m_CreatingScene{};
	};
}

#endif // SCENEMANAGER_H