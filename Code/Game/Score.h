#ifndef __SCORE_H
#define __SCORE_H

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

	virtual void OnEnter();
	virtual void Update();
	virtual void Render() const;
	virtual void KeyPressed(char key);

private:
	enum EState
	{
		eS_WaitingForFirstInitial,
		eS_WaitingForSecondInitial,
		eS_WaitingForThirdInitial,
		eS_SmallDelayBeforeShowingBestScores,
		eS_ShowingBestScores
	};
	EState m_eState;

	using BestScores =std::map<int, std::string, std::greater<int>>;
	BestScores m_BestScores;

	char m_cPlayerFirstInitial;
	char m_cPlayerSecondInitial;
	char m_cPlayerThirdInitial;

	int m_waitFrames;
};


#endif	// #ifndef __SCORE_H
