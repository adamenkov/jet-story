#include "Intro.h"
#include <cassert>
#include "../Shared/Engine.h"


Intro::Intro() : m_eIntroState(eIS_FirstScreen)
{
	m_pScreenSprite = new Sprite;
	m_pScreenSprite->SetTexture(new Texture("Assets/Intro1.png"));
}


void Intro::Render() const
{
	switch (m_eIntroState)
	{
	case eIS_FirstScreen:
	case eIS_SecondScreen:
		m_pScreenSprite->Render();
		break;

	case eIS_ThirdScreen:
		Engine::Print(10,  8, Engine::eC_Grey, "PC REMAKE BY");
		Engine::Print( 8, 11, Engine::eC_White, "EVGENY ADAMENKOV");
		Engine::Print(14, 13, Engine::eC_White, "2012");
		break;

	default:
		assert(!!!"Should not be here!");
	}

	Engine::Print(0, Engine::eScreenHeightInCharacters - 1, Engine::eC_Grey, "(PRESS ANY KEY TO CONTINUE)");
}


void Intro::KeyPressed(char UNUSED_PARAM(key))
{
	switch (m_eIntroState)
	{
	case eIS_FirstScreen:
		m_pScreenSprite->GetTexture()->LoadFromFile("Assets/Intro2.png");
		m_eIntroState = eIS_SecondScreen;
		break;

	case eIS_SecondScreen:
		delete m_pScreenSprite->GetTexture();
		delete m_pScreenSprite;
		m_eIntroState = eIS_ThirdScreen;
		break;

	case eIS_ThirdScreen:
		GameStates::SwitchTo("menu");
		break;

	default:
		assert(!!!"Should not be here!");
	}
}
