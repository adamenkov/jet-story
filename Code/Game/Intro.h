#pragma once

#include "../Shared/Engine.h"
#include "GameStates.h"


class Intro : public GameState
{
public:
	Intro();

	virtual void Render() const;
	virtual void KeyPressed(char key);

private:
	enum class EIntroState
	{
		FirstScreen,
		SecondScreen,
		ThirdScreen,
	};
	EIntroState m_eIntroState;

	std::unique_ptr<Sprite> m_pScreenSprite;
};
