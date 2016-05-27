#ifndef __ENGINE_H
#define __ENGINE_H

#pragma once

#define _USING_V110_SDK71_ 1


namespace Engine
{
	enum
	{
		eFPS = 50,

		eScreenScale = 3,

		eScreenWidthInChars		= 32,
		eScreenHeightInChars	= 24,

		eScreenWidthInPixels	= 8 * eScreenWidthInChars,
		eScreenHeightInPixels	= 8 * eScreenHeightInChars,
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

}	// namespace Engine


#include <d3d9.h>
#include "../Engine/Vector2.h"


namespace Engine
{
	extern void DrawText(int x, int y,    EColor eColor, const char* szText);
	extern void DrawText(const Vec2& pos, EColor eColor, const char* szText);
	extern void DrawText(const Vec2& pos, EColor eColor, char ch);

	extern void Print(int x, int y, EColor eColor, const char* szText);
	extern void Print(int x, int y, EColor eColor, char ch);

	extern void	LogError(const char* szFormat, ...);

	extern long int GetFrameID();

	extern bool	IsKeyDown(char key);

	extern void	Exit();

}	// namespace Engine

namespace Audio
{
	bool Load(const char* szFileName, const char* szName);

	bool IsPlaying(const char* szName);
	bool Play(const char* szName, int nLoopCount = 1);
	void Stop(const char* szName);
	void StopAll();

	void PauseAll();
	void ResumeAll();

}	// namespace Audio

#include "../Engine/Sprite.h"

#define UNUSED_PARAM(x)


#endif	// #ifndef __ENGINE_H
