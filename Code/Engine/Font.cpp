#define _USING_V110_SDK71_ 1

#include <cassert>
#include <fstream>
#include <Windows.h>
#include "Font.h"
#include "../Shared/Engine.h"
#include "Vector2.h"


Font::Font(const char* szFontImageFileName, int nLetterWidth, int nLetterHeight, int nColumns) 
{
	m_pTexture = new Texture(szFontImageFileName);

	if (!m_pTexture->GetD3DTexture()) {
		Engine::LogError("Error loading font image file: %s.", szFontImageFileName);
		assert(false);
		return;
	}

	SetTexture(m_pTexture, nLetterWidth, nLetterHeight, nColumns);
}


Font::~Font()
{
	delete m_pTexture;
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
