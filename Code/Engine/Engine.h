#ifndef __ENGINE_INTERNAL_H
#define __ENGINE_INTERNAL_H

#pragma once

#include "../Shared/Engine.h"
#include <d3dx9.h>


void DestroyWindow();
bool ApplicationWindowHasFocus();


extern LPDIRECT3DDEVICE9	g_pD3DDevice;
extern LPD3DXSPRITE			g_pSprites;

extern long int g_nFrameID;

class Font;
extern Font* g_pFont;


#endif	// #ifndef __ENGINE_INTERNAL_H
