#ifndef SELECTMODE_H
#define SELECTMODE_H

#include <map>
#include <string>

#include <Component.h>

namespace real
{
	class TextComponent;
}

enum class Modes : char
{
	singlePlayer = 0,
	coOp = 1,
	pvp = 2,
	amountOfModes = 3
};

class SelectMode final : public real::Component
{
public:
	explicit SelectMode(real::GameObject* pOwner);
	virtual ~SelectMode() override = default;

	SelectMode(const SelectMode& other) = delete;
	SelectMode& operator=(const SelectMode& rhs) = delete;
	SelectMode(SelectMode&& other) = delete;
	SelectMode& operator=(SelectMode&& rhs) = delete;

	virtual void Start() override;

	void Change(bool goUp);
	void ConfirmMode() const;

private:
	Modes m_CurrentMode{ Modes::singlePlayer };

	std::map<Modes, real::TextComponent*> m_TextComponents{};

	static inline std::map<Modes, std::string> m_ModeNames{
		{Modes::singlePlayer, "single player"},
		{Modes::coOp, "2 player co-op"},
		{Modes::pvp, "2 player pvp"}
	};

	void InitMode(char id);
};

#endif // SELECTMODE_H