#ifndef HIGHSCOREMENU_H
#define HIGHSCOREMENU_H

class HighScoreMenu final
{
public:
	explicit HighScoreMenu() = default;
	~HighScoreMenu() = default;

	HighScoreMenu(const HighScoreMenu& other) = delete;
	HighScoreMenu& operator=(const HighScoreMenu& rhs) = delete;
	HighScoreMenu(HighScoreMenu&& other) = delete;
	HighScoreMenu& operator=(HighScoreMenu&& rhs) = delete;

private:
	
};

#endif // HIGHSCOREMENU_H