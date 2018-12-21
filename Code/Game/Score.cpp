#include "Score.h"
#include <cassert>
#include <iomanip>
#include <iterator>
#include <sstream>
#include <string>
#include "../Shared/Engine.h"
#include "../Shared/Game.h"
#include "Player.h"
#include "Settings.h"
#include "Sounds.h"


Score::Score()
{
	m_BestScores[100000] = "TRC";
	m_BestScores[ 50000] = "CXL";
	m_BestScores[ 40000] = "FXT";
	m_BestScores[ 30000] = "CXL";
	m_BestScores[ 20000] = "ULT";
	m_BestScores[ 10000] = "PCH";
	m_BestScores[  5000] = "CXL";
	m_BestScores[  1000] = "DRT";
}


void Score::OnEnter()
{
	BestScores::iterator leastScore = m_BestScores.begin();
	std::advance(leastScore, m_BestScores.size() - 1);

	if (leastScore->first >= Player::GetPlayer()->GetScore())
	{
		m_eState = eS_ShowingBestScores;
		m_waitFrames = 50;
	}
	else
	{
		m_eState = eS_WaitingForFirstInitial;
		m_waitFrames = 0;
	}
}


void Score::Update()
{
	if (--m_waitFrames == 0)
	{
		if (m_eState == eS_SmallDelayBeforeShowingBestScores)
		{
			m_waitFrames = 50;
			m_eState = eS_ShowingBestScores;
		}
	}
}


void Score::Render() const
{
	if (m_eState == eS_ShowingBestScores)
	{
		Engine::Print(8, 2, Engine::eC_LightMagenta, "THE BEST GUNNERS");

		int place = 1;
		for (BestScores::const_iterator it = m_BestScores.begin(); it != m_BestScores.end(); ++it)
		{
			std::ostringstream os;
			os << place << ".  " << it->second << "   " << std::setw(6) << std::setfill('0') << it->first;
			Engine::Print(8, 2 * place + 4, Engine::eC_LightYellow, os.str());
			++place;
		}
		return;
	}

	Engine::Print(10, 8, Engine::eC_LightYellow, "GREAT SCORE !");
	Engine::Print(3, 12, Engine::eC_LightCyan, "PLEASE ENTER YOUR INITIALS");

	switch (m_eState)
	{
	case eS_WaitingForFirstInitial:
		Engine::Print(14, 17, Engine::eC_LightCyan, "###");
		Engine::Print(14, 17, Engine::eC_LightMagenta, "@@@");
		break;

	case eS_WaitingForSecondInitial:
		Engine::Print(14, 17, Engine::eC_White, m_cPlayerFirstInitial);
		Engine::Print(15, 17, Engine::eC_LightCyan, "##");
		Engine::Print(15, 17, Engine::eC_LightMagenta, "@@");
		break;

	case eS_WaitingForThirdInitial:
		Engine::Print(14, 17, Engine::eC_White, m_cPlayerFirstInitial);
		Engine::Print(15, 17, Engine::eC_White, m_cPlayerSecondInitial);
		Engine::Print(16, 17, Engine::eC_LightCyan, '#');
		Engine::Print(16, 17, Engine::eC_LightMagenta, '@');
		break;

	case eS_SmallDelayBeforeShowingBestScores:
		Engine::Print(14, 17, Engine::eC_White, m_cPlayerFirstInitial);
		Engine::Print(15, 17, Engine::eC_White, m_cPlayerSecondInitial);
		Engine::Print(16, 17, Engine::eC_White, m_cPlayerThirdInitial);
		break;

	default:
		assert(!"Should not be here!");
	}
}


void Score::KeyPressed(char key)
{
	if (m_waitFrames > 0)
		return;

	switch (m_eState)
	{
	case eS_WaitingForFirstInitial:
		m_cPlayerFirstInitial = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_eState = eS_WaitingForSecondInitial;
		m_waitFrames = 20;
		break;

	case eS_WaitingForSecondInitial:
		m_cPlayerSecondInitial = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_eState = eS_WaitingForThirdInitial;
		m_waitFrames = 20;
		break;

	case eS_WaitingForThirdInitial:
	{
		m_cPlayerThirdInitial = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_BestScores[ Player::GetPlayer()->GetScore() ] = std::string() + m_cPlayerFirstInitial + m_cPlayerSecondInitial + m_cPlayerThirdInitial;
		BestScores::iterator leastScore = m_BestScores.begin();
		std::advance(leastScore, m_BestScores.size() - 1);
		m_BestScores.erase(leastScore);
		m_eState = eS_SmallDelayBeforeShowingBestScores;
		m_waitFrames = 20;
		break;
	}
	
	case eS_ShowingBestScores:
		// Start music from the beginning in the main menu
		if (Settings::bMusic && Audio::IsPlaying(Sounds::MAIN_THEME))
		{
			Audio::Stop(Sounds::MAIN_THEME);
		}
		GameStates::SwitchTo("menu");
		break;
	
	default:
		assert(!"Should not be here!");
	}
}
