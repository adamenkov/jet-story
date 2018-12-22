#define _USING_V110_SDK71_ 1

#include <cassert>
#include <fstream>
#include <Windows.h>
#include "Font.h"
#include "../Shared/Engine.h"
#include "Vector2.h"


Font::Font(const std::string& sFontImageFileName, int nLetterWidth, int nLetterHeight, int nColumns)
{
	std::shared_ptr<Texture> pTexture = std::make_shared<Texture>(sFontImageFileName);

	if (!pTexture->GetDirect3DTexture())
	{
		Engine::LogError("Error loading font image file: %s.", sFontImageFileName.c_str());
		assert(false);
		return;
	}

	m_fontSprite = std::make_unique<Sprite>();
	m_fontSprite->SetTexture(pTexture, nLetterWidth, nLetterHeight, nColumns);
}


void Font::Render(int x, int y, EColor eColor, const std::string& text)
{
	m_fontSprite->SetColor(eColor);
	Vector2 pos(static_cast<float>(x), static_cast<float>(y));

	for (char c : text)
	{
		m_fontSprite->SetAnimationFrame(c);
		m_fontSprite->SetPos(pos);
		m_fontSprite->Render();
		pos.x += m_fontSprite->GetWidth();
	}
}
