#ifndef __ENGINE_SHARED_H
#define __ENGINE_SHARED_H

#pragma once

#define _USING_V110_SDK71_ 1
#include <d3d9.h>
#include <string>
#include "../Engine/Vector2.h"


namespace Engine
{
	enum
	{
		eFPS = 50,

		eScreenScale = 3,

		eScreenWidthInCharacters	= 32,
		eScreenHeightInCharacters	= 24,

		eCharacterWidthInPixels		= 8,
		eCharacterHeightInPixels	= 8,

		eScreenWidthInPixels	= eCharacterWidthInPixels * eScreenWidthInCharacters,
		eScreenHeightInPixels	= eCharacterHeightInPixels * eScreenHeightInCharacters,
	};


	enum EColor
	{
		eC_Black,
		eC_Blue,
		eC_Red,
		eC_Magenta,
		eC_Green,
		eC_Cyan,
		eC_Yellow,
		eC_Grey,

		eC_LightBlack,
		eC_LightBlue,
		eC_LightRed,
		eC_LightMagenta,
		eC_LightGreen,
		eC_LightCyan,
		eC_LightYellow,
		eC_White,

		eC_TotalColors
	};


	extern void DrawText(int x, int y,       EColor eColor, const std::string& text);
	extern void DrawText(const Vector2& pos, EColor eColor, const std::string& text);
	extern void DrawText(const Vector2& pos, EColor eColor, char ch);

	extern void Print(int x, int y, EColor eColor, const std::string& text);
	extern void Print(int x, int y, EColor eColor, char ch);

	extern void	LogError(const char* szFormat, ...);

	extern long int GetFrameID();

	extern bool	IsKeyDown(char key);

	extern void	Exit();
}	// namespace Engine


namespace Audio
{
	bool Load(const std::string& fileName, const std::string& name);

	bool IsPlaying(const std::string& name);
	bool Play(const std::string& name, int nLoopCount = 1);
	void Stop(const std::string& name);
	void StopAll();

	void PauseAll();
	void ResumeAll();
}	// namespace Audio


// Don't move this.
//#include "../Engine/Sprite.h"


#define UNUSED_PARAM(x)


#endif	// #ifndef __ENGINE_SHARED_H
