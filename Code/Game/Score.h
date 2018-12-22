#pragma once

#define _USING_V110_SDK71_ 1

#include <functional>
#include <map>
#include <string>
#include "GameStates.h"


class Score : public GameState
{
public:
	Score();

	virtual void OnEnter() override;
	virtual void Update() override;
	virtual void Render() const override;
	virtual void KeyPressed(char key) override;

private:
	enum class EState
	{
		WaitingForFirstInitial,
		WaitingForSecondInitial,
		WaitingForThirdInitial,
		SmallDelayBeforeShowingBestScores,
		ShowingBestScores
	};
	EState m_eState;

	using BestScores = std::map<int, std::string, std::greater<int>>;
	BestScores m_BestScores;

	char m_cPlayerFirstInitial;
	char m_cPlayerSecondInitial;
	char m_cPlayerThirdInitial;

	int m_waitFrames;
};
