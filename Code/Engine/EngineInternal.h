#pragma once

#include "../Shared/Engine.h"
#include <d3dx9.h>


void DestroyWindow();
bool ApplicationWindowHasFocus();


extern LPDIRECT3DDEVICE9	g_pDirect3DDevice;
extern LPD3DXSPRITE			g_pDirect3DXSprite;

extern long int g_nFrameID;

class Font;
extern std::unique_ptr<Font> g_pFont;
