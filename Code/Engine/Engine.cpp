#include "../Shared/Engine.h"
#include <cstdarg>
#include <fstream>
#include <d3d9.h>
#include <Windows.h>
#include "../Shared/Game.h"
#include "Common.h"
#include "Font.h"
#include "Vector2.h"


namespace Engine
{
	void DrawText(int x, int y, EColor eColor, const char* szText)
	{
		g_pFont->Render(x, y, eColor, szText);
	}


	void DrawText(const Vector2& pos, EColor eColor, const char* szText)
	{
		g_pFont->Render(int(pos.x), int(pos.y), eColor, szText);
	}


	void DrawText(const Vector2& pos, EColor eColor, char ch)
	{
		char szText[2];
		szText[0] = ch;
		szText[1] = 0;
		g_pFont->Render(int(pos.x), int(pos.y), eColor, szText);
	}


	void Print(int x, int y, EColor eColor, const char* szText)
	{
		DrawText(eCharacterWidthInPixels * x, eCharacterHeightInPixels * y, eColor, szText);
	}


	void Print(int x, int y, EColor eColor, char ch)
	{
		char szText[2];
		szText[0] = ch;
		szText[1] = 0;
		DrawText(eCharacterWidthInPixels * x, eCharacterHeightInPixels * y, eColor, szText);
	}


	void LogError(const char* szFormat, ...)
	{
		static std::ofstream logFile("Game.log");

		va_list	args;
		char szBuffer[1000];
		va_start(args, szFormat);
		vsprintf_s(szBuffer, sizeof szBuffer, szFormat, args);
		va_end(args);
		logFile << "ERROR: " << szBuffer << std::endl;
	}


	long int GetFrameID()
	{
		return g_nFrameID;
	}

	
	bool IsKeyDown(char key)
	{
		return (HasFocus() && (GetAsyncKeyState(key) < 0));
	}


	void Exit()
	{
		ExitEngine();
	}

}	// namespace Engine
