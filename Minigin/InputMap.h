#ifndef INPUTMAP_H
#define INPUTMAP_H

#include "Command.h"
#include "InputTypes.h"

namespace dae
{
	class InputMap final
	{
	public:
		explicit InputMap(std::string name);
		~InputMap() = default;

		InputMap(const InputMap& other) = delete;
		InputMap& operator=(const InputMap& rhs) = delete;
		InputMap(InputMap&& other) = delete;
		InputMap& operator=(InputMap&& rhs) = delete;

		template <class CommandType, typename... CommandArgs>
			requires std::is_base_of_v<Command, CommandType>
		void AddKeyboardAction(uint8_t id, KeyState event, uint32_t scancode, CommandArgs... commandArgs);
		template <class CommandType, typename... CommandArgs>
			requires std::is_base_of_v<Command, CommandType>
		void AddGamePadAction(uint8_t controllerId, KeyState inputType, GamePad::Button button, CommandArgs... commandArgs);

		const std::map<uint8_t, std::unique_ptr<KeyboardAction>>& GetKeyboardActions() const { return m_pKeyboardActions; }
		const std::map<uint8_t, std::vector<std::unique_ptr<ControllerAction>>>& GetGamePadActions() const { return m_pControllerActions; }

	private:
		std::string m_Name;

		std::map<uint8_t, std::unique_ptr<KeyboardAction>> m_pKeyboardActions{};
		std::map<uint8_t, std::vector<std::unique_ptr<ControllerAction>>> m_pControllerActions{};

		static bool IsKeyCodeValid(int code);
	};

	template<class CommandType, typename ...CommandArgs>
		requires std::is_base_of_v<Command, CommandType>
	void InputMap::AddKeyboardAction(uint8_t id, KeyState event, uint32_t scancode, CommandArgs ...commandArgs)
	{
		if (m_pKeyboardActions.contains(id))
			throw std::runtime_error("A keyboard input is already registered with id: {}" + id);

		if (IsKeyCodeValid(static_cast<int>(scancode)) == false)
			throw std::runtime_error(scancode + " is not a valid scancode");

		m_pKeyboardActions.try_emplace(id, std::make_unique<KeyboardAction>(event, scancode, new CommandType(commandArgs...)));
	}

	template <class CommandType, typename ... CommandArgs>
		requires std::is_base_of_v<Command, CommandType>
	void InputMap::AddGamePadAction(uint8_t controllerId, KeyState inputType, GamePad::Button button,
		CommandArgs... commandArgs)
	{
		//if (m_pControllerActions.contains(controllerId))
		//{
		//	Logger::LogWarning({ "A game pad input is already registered with id: {}" }, controllerId);
		//	return;
		//}

		m_pControllerActions[controllerId].push_back(std::make_unique<ControllerAction>(controllerId, inputType, button, new CommandType(commandArgs...)));
	}
}

#endif // INPUTMAP_H