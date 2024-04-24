#ifndef HIGHSCOREDISPLAY_H
#define HIGHSCOREDISPLAY_H

#include <Component.h>

namespace real
{
	class TextComponent;
}

class HighScoreDisplay final : public real::Component
{
public:
	explicit HighScoreDisplay(real::GameObject* pOwner);
	virtual ~HighScoreDisplay() override = default;

	HighScoreDisplay(const HighScoreDisplay& other) = delete;
	HighScoreDisplay& operator=(const HighScoreDisplay& rhs) = delete;
	HighScoreDisplay(HighScoreDisplay&& other) = delete;
	HighScoreDisplay& operator=(HighScoreDisplay&& rhs) = delete;

	virtual void Start() override;

	void CheckForHighScore(int score) const;
	static int GetHighScore() { return m_HighScore; }

private:
	static inline int m_HighScore{ 0 };
	real::TextComponent* m_pTextComponent{ nullptr };

	int LoadHighScore(bool singlePlayer) const;
};

#endif // HIGHSCOREDISPLAY_H