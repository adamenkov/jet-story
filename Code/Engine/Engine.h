
#pragma once

#include "../Shared/Engine.h"
#include <d3dx9.h>


void ExitEngine();
bool HasFocus();


extern LPDIRECT3DDEVICE9	g_pD3DDevice;
extern LPD3DXSPRITE			g_pSprites;

extern long int g_nFrameID;

class Font;
extern Font* g_pFont;


