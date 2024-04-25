#ifndef ENTERNAME_H
#define ENTERNAME_H

#include <array>

#include <Component.h>
#include <Subject.h>

namespace real
{
	class TextComponent;
}

class FlickerText;

class EnterName final : public real::Component
{
public:
	enum class Events : char
	{
		characterEntered = 0,
		nameConfirmed = 1,
	};

	explicit EnterName(real::GameObject* pOwner);
	virtual ~EnterName() override = default;

	EnterName(const EnterName& other) = delete;
	EnterName& operator=(const EnterName& rhs) = delete;
	EnterName(EnterName&& other) = delete;
	EnterName& operator=(EnterName&& rhs) = delete;

	virtual void Start() override;

	void EnterCharacter(int controllerId);
	void ChangeCharacter(bool up);

	real::Subject<Events, char> characterEntered;
	real::Subject<Events, const std::string&> nameEntered;

private:
	static constexpr inline int max_amount_of_characters{ 3 };
	int m_CurrentPosition{ 0 };
	char m_CurrentCharacter{ 'A' };

	std::array<std::pair<char, std::pair<real::TextComponent*, FlickerText*>>, max_amount_of_characters> m_Name{};

	static constexpr inline char lowest_char{ 'A' };
	static constexpr inline char highest_char{ 'Z' };

	void AddTextComponent(size_t id);
};

#endif // ENTERNAME_H