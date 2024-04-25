#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <array>
#include <map>

#include <Component.h>
#include <Observer.h>
#include <glm/fwd.hpp>

#include "EnterName.h"
#include "Macros.h"

namespace real
{
	class TextComponent;
}

class LeaderBoard final
	: public real::Component
	, public real::Observer<EnterName::Events, char>
	, public real::Observer<EnterName::Events, const std::string&>
{
public:
	explicit LeaderBoard(real::GameObject* pOwner);
	virtual ~LeaderBoard() override;

	LeaderBoard(const LeaderBoard& other) = delete;
	LeaderBoard& operator=(const LeaderBoard& rhs) = delete;
	LeaderBoard(LeaderBoard&& other) = delete;
	LeaderBoard& operator=(LeaderBoard&& rhs) = delete;

	virtual void Start() override;

	void HandleEvent(EnterName::Events, char) override;
	void HandleEvent(EnterName::Events, const std::string&) override;
	void OnSubjectDestroy() override;

	static void WriteCategories(real::GameObject* pOwner, float localYPos, const glm::u8vec4& color);
	static constexpr inline float place_offset{ -(83 * PIXEL_SCALE) };
	static constexpr inline float score_offset{ -(38 * PIXEL_SCALE) };
	static constexpr inline float act_offset{ 21 * PIXEL_SCALE };
	static constexpr inline float name_offset{ 75 * PIXEL_SCALE };

private:
	struct Data
	{
		int place{}, score{}, act{};
		std::string name{};
	};
	
	std::array<Data, 5> m_LeaderBoard{};
	std::string m_File;
	real::TextComponent* m_pPlayerName{};
	uint32_t m_PLayerNameId{};

	void LoadLeaderBoard(bool singlePlayer);
	void InsertPlayerScore(int score);
	void SaveLeaderBoard(bool singlePlayer);

	void WriteData(const Data& data);


	static inline std::map<int, std::string> m_PlaceToString{
		{1, "1st"},
		{2, "2nd"},
		{3, "3rd"},
		{4, "4th"},
		{5, "5th"},
	};
};

#endif // LEADERBOARD_H