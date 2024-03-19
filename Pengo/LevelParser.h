#ifndef LEVELPARSER_H
#define LEVELPARSER_H
#include <xstring>

class LevelParser final
{
public:
	explicit LevelParser() = default;
	~LevelParser() = default;

	LevelParser(const LevelParser& other) = delete;
	LevelParser& operator=(const LevelParser& rhs) = delete;
	LevelParser(LevelParser&& other) = delete;
	LevelParser& operator=(LevelParser&& rhs) = delete;

private:
	
};

#endif // LEVELPARSER_H