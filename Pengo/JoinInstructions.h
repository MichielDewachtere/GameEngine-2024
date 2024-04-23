#ifndef JOININSTRUCTIONS_H
#define JOININSTRUCTIONS_H

#include <Component.h>

namespace real
{
	class TextComponent;
}

class JoinInstructions final : public real::Component
{
public:
	explicit JoinInstructions(real::GameObject* pOwner);
	virtual ~JoinInstructions() override = default;

	JoinInstructions(const JoinInstructions& other) = delete;
	JoinInstructions& operator=(const JoinInstructions& rhs) = delete;
	JoinInstructions(JoinInstructions&& other) = delete;
	JoinInstructions& operator=(JoinInstructions&& rhs) = delete;

	virtual void Start() override;
	virtual void Update() override;

	void PlayerJoined(int controllerId);

private:
	float m_FlickerTime{ 1.f }, m_AccuTime{ 0 };
	bool m_IsYellow{ true };
	real::TextComponent* m_pTextComponent{ nullptr };

	static inline int m_RegisteredPlayers{ 0 };
};

#endif // JOININSTRUCTIONS_H