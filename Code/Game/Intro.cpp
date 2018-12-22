#include "Intro.h"
#include <cassert>
#include "../Shared/Engine.h"


Intro::Intro() : m_eIntroState(EIntroState::FirstScreen)
{
	m_pScreenSprite = std::make_unique<Sprite>();
	m_pScreenSprite->SetTexture(std::make_shared<Texture>("Assets/Intro1.png"));
}


void Intro::Render() const
{
	switch (m_eIntroState)
	{
	case EIntroState::FirstScreen:
	case EIntroState::SecondScreen:
		m_pScreenSprite->Render();
		break;

	case EIntroState::ThirdScreen:
		Engine::Print(10,  8, EColor::eC_Grey, "PC REMAKE BY");
		Engine::Print( 8, 11, EColor::eC_White, "EVGENY ADAMENKOV");
		Engine::Print(14, 13, EColor::eC_White, "2019");
		break;
	}

	Engine::Print(0, Engine::eScreenHeightInCharacters - 1, EColor::eC_Grey, "(PRESS ANY KEY TO CONTINUE)");
}


void Intro::KeyPressed(char UNUSED_PARAM(key))
{
	switch (m_eIntroState)
	{
	case EIntroState::FirstScreen:
		m_pScreenSprite->GetTexture()->LoadFromFile("Assets/Intro2.png");
		m_eIntroState = EIntroState::SecondScreen;
		break;

	case EIntroState::SecondScreen:
		m_eIntroState = EIntroState::ThirdScreen;
		break;

	case EIntroState::ThirdScreen:
		GameStates::SwitchTo("menu");
		break;
	}
}
