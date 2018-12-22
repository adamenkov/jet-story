#pragma once

#include "Sprite.h"
#include <string>


class Font
{
public:
	Font(const std::string& sFontImageFileName, int nLetterWidth, int nLetterHeight, int nColumns);

	bool IsEmpty() const { return !m_fontSprite->HasTexture(); }

	void Render(int x, int y, EColor eColor, const std::string& text);

private:
	std::unique_ptr<Sprite> m_fontSprite;
};
