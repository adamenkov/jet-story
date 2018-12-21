#include "Menu.h"
#include <cassert>
#include <fstream>
#include <string>
#include "../Shared/Engine.h"
#include "../Shared/Game.h"
#include "Settings.h"
#include "Sounds.h"


Menu::Menu() :
	m_eState(eMS_MainMenu)
{
	std::ifstream fileRunningLine("Assets/RunningLine.txt");
	m_sRunningLine.assign(
		std::istreambuf_iterator<char>(fileRunningLine),
		std::istreambuf_iterator<char>()
	);
}


void Menu::OnEnter()
{
	m_eState = eMS_MainMenu;

	if (Settings::bMusic)
	{
		if (!Audio::IsPlaying(Sounds::MAIN_THEME))
		{
			Audio::PlayLooped(Sounds::MAIN_THEME);
		}
	}
	else
	{
		Audio::Stop(Sounds::MAIN_THEME);
	}

	m_nFPSCounter = 0;

	m_waitFrames = 0;
}


void Menu::Update()
{
	++m_nFPSCounter;

	if (m_waitFrames > 0)
	{
		if (--m_waitFrames == 0)
		{
			switch (m_eState)
			{
			case eMS_AssigningKey_Left:		m_eState = eMS_AssigningKey_Right;	break;
			case eMS_AssigningKey_Right:	m_eState = eMS_AssigningKey_Down;	break;
			case eMS_AssigningKey_Down:		m_eState = eMS_AssigningKey_Up;		break;
			case eMS_AssigningKey_Up:		m_eState = eMS_AssigningKey_Fire;	break;
			case eMS_AssigningKey_Fire:		m_eState = eMS_MainMenu;			break;
			
			case eMS_MainMenu:
				break;

			default:
				assert(!"Should not be here!");
			}
		}
	}
}


void Menu::Render() const
{
	if (m_eState == eMS_AssigningKey_Fire)
	{
		if ((Settings::cKeyLeft  == 'K') &&
			(Settings::cKeyRight == 'A') &&
			(Settings::cKeyDown  == 'R') &&
			(Settings::cKeyUp    == 'E') &&
			(Settings::cKeyFire  == 'L'))
		{
			DrawBorder();

			if (m_waitFrames == 40)
			{
				Settings::bInvulnerability = true;
				Audio::Play(Sounds::SHHH);
			}
		}
	}

	switch (m_eState)
	{
	case eMS_MainMenu:
	case eMS_GetReadyForSession:
		Engine::Print(12,  5, Engine::eC_White, "JET-STORY");

		Engine::Print( 2, 13, Engine::eC_Grey,  "1.  REDEFINE KEYS");
		
		Engine::Print( 2, 15, Engine::eC_Grey,  "2.  SOUND EFFECTS");
		Engine::Print(20, 15, Settings::bSoundEffects ? Engine::eC_White : Engine::eC_LightMagenta, "ON");
		Engine::Print(22, 15, Engine::eC_Grey,  "/");
		Engine::Print(23, 15, Settings::bSoundEffects ? Engine::eC_LightMagenta : Engine::eC_White, "OFF");

		Engine::Print( 2, 17, Engine::eC_Grey,  "3.  MUSIC");
		Engine::Print(12, 17, Settings::bMusic ? Engine::eC_White : Engine::eC_LightMagenta, "ON");
		Engine::Print(14, 17, Engine::eC_Grey,  "/");
		Engine::Print(15, 17, Settings::bMusic ? Engine::eC_LightMagenta : Engine::eC_White, "OFF");

		Engine::Print( 2, 19, Engine::eC_Grey,  "4.  START GAME");


		enum { y = 8 * (Engine::eScreenHeightInCharacters - 1) };

		Engine::DrawText(
			-m_nFPSCounter % 8,
			y,
			Engine::eC_Cyan,
			m_sRunningLine.substr(
				(m_nFPSCounter / 8) % m_sRunningLine.length(), 
				Engine::eScreenWidthInCharacters
			)
		);

		Engine::Print(0,
			Engine::eScreenHeightInCharacters - 1, Engine::eC_Black, '\x1F');
		Engine::Print(Engine::eScreenWidthInCharacters - 1,
			Engine::eScreenHeightInCharacters - 1, Engine::eC_Black, '\x1F');

		break;
		
	case eMS_AssigningKey_Fire:
		Engine::Print(12,  17, Engine::eC_LightYellow, "FIRE");
		Engine::Print(18,  17, Engine::eC_LightYellow, Settings::cKeyFire);
	case eMS_AssigningKey_Up:
		Engine::Print(12,  16, Engine::eC_LightYellow, "UP");
		Engine::Print(18,  16, Engine::eC_LightYellow, Settings::cKeyUp);
	case eMS_AssigningKey_Down:
		Engine::Print(12,  15, Engine::eC_LightYellow, "DOWN");
		Engine::Print(18,  15, Engine::eC_LightYellow, Settings::cKeyDown);
	case eMS_AssigningKey_Right:
		Engine::Print(12,  14, Engine::eC_LightYellow, "RIGHT");
		Engine::Print(18,  14, Engine::eC_LightYellow, Settings::cKeyRight);
	case eMS_AssigningKey_Left:
		Engine::Print(12,  13, Engine::eC_LightYellow, "LEFT");
		Engine::Print(18,  13, Engine::eC_LightYellow, Settings::cKeyLeft);
		break;
	}
}


void Menu::KeyPressed(char key)
{
	if (m_waitFrames > 0)
		return;

	switch (m_eState)
	{
	case eMS_MainMenu:
		Audio::Play(Sounds::KEY_PRESSED);

		switch (key)
		{
		case '1':
			Audio::Play(Sounds::REDEFINE_KEYS);
			Settings::cKeyLeft	= ' ';
			Settings::cKeyRight	= ' ';
			Settings::cKeyDown	= ' ';
			Settings::cKeyUp	= ' ';
			Settings::cKeyFire	= ' ';
			m_eState = eMS_AssigningKey_Left;
			break;

		case '2':
			Settings::bSoundEffects = !Settings::bSoundEffects;
			break;

		case '3':
			Settings::bMusic = !Settings::bMusic;
			if (Settings::bMusic)
			{
				Audio::PlayLooped(Sounds::MAIN_THEME);
			}
			else
			{
				Audio::Stop(Sounds::MAIN_THEME);
			}
			break;

		case '4':
			m_eState = eMS_GetReadyForSession;
			break;

		default:
			m_waitFrames = 6;
		}
		break;

	case eMS_GetReadyForSession:
		Audio::Play(Sounds::KEY_DEFINED);
		GameStates::SwitchTo("session");
		break;

	case eMS_AssigningKey_Left:
		Settings::cKeyLeft = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_waitFrames = 20;
		break;

	case eMS_AssigningKey_Right:
		Settings::cKeyRight = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_waitFrames = 20;
		break;

	case eMS_AssigningKey_Down:
		Settings::cKeyDown = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_waitFrames = 20;
		break;

	case eMS_AssigningKey_Up:
		Settings::cKeyUp = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_waitFrames = 20;
		break;

	case eMS_AssigningKey_Fire:
		Settings::cKeyFire = key;
		Audio::Play(Sounds::KEY_DEFINED);
		m_waitFrames =
			((Settings::cKeyLeft  == 'K') &&
			 (Settings::cKeyRight == 'A') &&
			 (Settings::cKeyDown  == 'R') &&
			 (Settings::cKeyUp    == 'E') &&
			 (Settings::cKeyFire  == 'L'))
			? 50 : 20;
		break;

	default:
		assert(!"Should not be here!");
	}
}


void Menu::DrawBorder() const
{
	const char* szScreenLine = "________________________________";

	for (int i = 0; i < 8; ++i)
	{
		Engine::DrawText(0, i - 7, GetRandomBorderColor(), szScreenLine);
	}
	for (int i = 8; i < Engine::eScreenHeightInPixels - 8; ++i)
	{
		Engine::DrawText(0, i - 7, GetRandomBorderColor(), "_                              _");
	}
	for (int i = Engine::eScreenHeightInPixels - 8; i < Engine::eScreenHeightInPixels; ++i)
	{
		Engine::DrawText(0, i - 7, GetRandomBorderColor(), szScreenLine);
	}
}
