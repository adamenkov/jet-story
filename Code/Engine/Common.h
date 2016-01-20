#ifndef __COMMON_H
#define __COMMON_H

#pragma once

#include <d3dx9.h>


void ExitEngine();
bool HasFocus();


extern LPDIRECT3DDEVICE9	g_pD3DDevice;
extern LPD3DXSPRITE			g_pSprites;

extern long int g_nFrameID;

class Font;
extern Font* g_pFont;


#endif	// #ifndef __COMMON_H
