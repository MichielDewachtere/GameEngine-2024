#ifndef COMMAND_H
#define COMMAND_H

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		explicit Command() = default;
		virtual ~Command() = default;

		Command(const Command& other) = delete;
		Command& operator=(const Command& rhs) = delete;
		Command(Command&& other) = delete;
		Command& operator=(Command&& rhs) = delete;

		virtual void Start() {}
		virtual void Execute() = 0;
	};

	class GameObjectCommand : public Command
	{
	public:
		explicit GameObjectCommand(GameObject* pGameObject)
			: Command(), m_pGameObject(pGameObject) {}
		virtual ~GameObjectCommand() override = default;

		GameObjectCommand(const GameObjectCommand& other) = delete;
		GameObjectCommand& operator=(const GameObjectCommand& rhs) = delete;
		GameObjectCommand(GameObjectCommand&& other) = delete;
		GameObjectCommand& operator=(GameObjectCommand&& rhs) = delete;

	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }

	private:
		GameObject* m_pGameObject;
	};

	class TestCommand final : public Command
	{
	public:
		explicit TestCommand() = default;
		virtual ~TestCommand() override = default;

		virtual void Execute() override;
	};
}

#endif // COMMAND_H