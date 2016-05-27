#ifndef __FONT_H
#define __FONT_H

#pragma once

#include "Sprite.h"


class Font : public Sprite
{
public:
	Font(const char* szFontImageFileName, int nLetterWidth, int nLetterHeight, int nColumns);

	virtual ~Font();

	virtual void Render(int x, int y, Engine::EColor eColor, const char* szText);
};


#endif	// #ifndef __FONT_H
