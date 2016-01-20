#include <cassert>
#include <fstream>
#include <Windows.h>
#include "Font.h"
#include "../Common/Engine.h"
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


void Font::Render(int x, int y, Engine::EColor eColor, const char* szText)
{
	SetColor(eColor);

	for (Vec2 pos(static_cast<float>(x), static_cast<float>(y)); char ch = *szText++; pos.x += m_nWidth)
	{
		SetAnimationFrame(ch);
		SetPos(pos);
		Sprite::Render();
	}
}
