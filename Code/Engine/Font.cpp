#define _USING_V110_SDK71_ 1

#include <cassert>
#include <fstream>
#include <Windows.h>
#include "Font.h"
#include "../Shared/Engine.h"
#include "Vector2.h"


Font::Font(const char* szFontImageFileName, int nLetterWidth, int nLetterHeight, int nColumns) 
{
	Texture* pTexture = new Texture(szFontImageFileName);

	if (!pTexture->GetDirect3DTexture()) {
		Engine::LogError("Error loading font image file: %s.", szFontImageFileName);
		assert(false);
		return;
	}

	m_fontSprite.SetTexture(pTexture, nLetterWidth, nLetterHeight, nColumns);
}


Font::~Font()
{
	delete pTexture;
}


void Font::Render(int x, int y, Engine::EColor eColor, const std::string& text)
{
	SetColor(eColor);
	Vector2 pos(static_cast<float>(x), static_cast<float>(y));

	for (std::string::const_iterator it = text.begin(), itEnd = text.end(); it != itEnd; ++it)
	{
		SetAnimationFrame(*it);
		SetPos(pos);
		Sprite::Render();
		pos.x += m_nWidth;
	}
}
