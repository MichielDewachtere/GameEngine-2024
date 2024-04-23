#ifndef ENTERNAME_H
#define ENTERNAME_H

#include <array>
#include <cstdint>

#include <Component.h>

namespace real
{
	class TextComponent;
}

class EnterName final : public real::Component
{
public:
	explicit EnterName(real::GameObject* pOwner);
	virtual ~EnterName() override = default;

	EnterName(const EnterName& other) = delete;
	EnterName& operator=(const EnterName& rhs) = delete;
	EnterName(EnterName&& other) = delete;
	EnterName& operator=(EnterName&& rhs) = delete;

	virtual void Start() override;

	void EnterCharacter(int controllerId);
	void ChangeCharacter(bool up);

	void LinkPlayer(uint8_t playerId) { m_LinkedPlayer = playerId; }

private:
	static constexpr inline int max_amount_of_characters{ 3 };
	int m_CurrentPosition{ 0 };
	char m_CurrentCharacter{ 'A' };

	std::array<std::pair<char, real::TextComponent*>, max_amount_of_characters> m_Name{};

	uint8_t m_LinkedPlayer;

	static constexpr inline char lowest_char{ 'A' };
	static constexpr inline char highest_char{ 'Z' };

	void AddTextComponent(size_t id);
};

#endif // ENTERNAME_H