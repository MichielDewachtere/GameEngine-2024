#ifndef REGISTERHIGHSCORE_H
#define REGISTERHIGHSCORE_H

#include <Component.h>

class RegisterHighScore final : public real::Component
{
public:
	explicit RegisterHighScore(real::GameObject* pOwner);
	virtual ~RegisterHighScore() override = default;

	RegisterHighScore(const RegisterHighScore& other) = delete;
	RegisterHighScore& operator=(const RegisterHighScore& rhs) = delete;
	RegisterHighScore(RegisterHighScore&& other) = delete;
	RegisterHighScore& operator=(RegisterHighScore&& rhs) = delete;

	virtual void Start() override;

private:
	void WriteData() const;
	static void AddCommands(real::GameObject* enterName);
};

#endif // REGISTERHIGHSCORE_H