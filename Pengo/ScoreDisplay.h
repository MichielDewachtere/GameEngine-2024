#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <Component.h>
#include <map>

class Player;

namespace real
{
	class TextComponent;
}

enum class ScoreEvents : char
{
	bonusTimeUnder20,
	bonusTimeUnder30,
	bonusTimeUnder40,
	bonusTimeUnder50,
	bonusTimeUnder60,

	starBlock,
	starBlockWall,

	kill,
	doubleKill,
	tripleKill,
	quadKill,

	stunKill,

	breakIce,
	breakEgg,

	null
};

class ScoreDisplay final : public real::Component
{
public:
	explicit ScoreDisplay(real::GameObject* pOwner);
	virtual ~ScoreDisplay() override = default;

	ScoreDisplay(const ScoreDisplay& other) = delete;
	ScoreDisplay& operator=(const ScoreDisplay& rhs) = delete;
	ScoreDisplay(ScoreDisplay&& other) = delete;
	ScoreDisplay& operator=(ScoreDisplay&& rhs) = delete;

	virtual void Start() override;
	void AddScore(ScoreEvents event);

	uint32_t GetScore() const { return m_Score; }

	void Reset();

private:
	uint32_t m_Score{ 0 };
	real::TextComponent* m_pTextComponent{ nullptr };

	const static inline std::map<ScoreEvents, int> event_to_points
	{
		{ScoreEvents::bonusTimeUnder20,	5'000	},
		{ScoreEvents::bonusTimeUnder30,	2'000	},
		{ScoreEvents::bonusTimeUnder40,	1'000	},
		{ScoreEvents::bonusTimeUnder50,	500		},
		{ScoreEvents::bonusTimeUnder60,	10		},
		{ScoreEvents::starBlock,			10'000	},
		{ScoreEvents::starBlockWall,		5'000	},
		{ScoreEvents::kill,				400		},
		{ScoreEvents::doubleKill,			1'600	},
		{ScoreEvents::tripleKill,			3'200	},
		{ScoreEvents::quadKill,			6'400	},
		{ScoreEvents::stunKill,			100		},
		{ScoreEvents::breakIce,			30		},
		{ScoreEvents::breakEgg,			500		},
		{ScoreEvents::null ,				0		},
	};
};

#endif // SCOREDISPLAY_H