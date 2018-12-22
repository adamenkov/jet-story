#pragma once

#define _USING_V110_SDK71_ 1
#include <d3d9.h>
#include <string>
#include "../Engine/Vector2.h"


enum class EColor
{
	Black,
	Blue,
	Red,
	Magenta,
	Green,
	Cyan,
	Yellow,
	Grey,

	LightBlack,
	LightBlue,
	LightRed,
	LightMagenta,
	LightGreen,
	LightCyan,
	LightYellow,
	White,

	TotalColors
};


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
	bool Play(const std::string& name);
	bool PlayLooped(const std::string& name);
	void Stop(const std::string& name);
	void StopAll();

	void PauseAll();
	void ResumeAll();
}	// namespace Audio


#include "../Engine/Sprite.h"


#define UNUSED_PARAM(x)
