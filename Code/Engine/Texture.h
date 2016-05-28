#ifndef __TEXTURE_H
#define __TEXTURE_H

#pragma once

#define _USING_V110_SDK71_ 1
#include <d3d9.h>
#include <D3dx9tex.h>
#include <string>
#include <vector>


class Texture
{
public:
	Texture(const std::string& fileName = std::string(), D3DCOLOR colorTransparent = D3DCOLOR_XRGB(0, 0, 0));
	~Texture();

	LPDIRECT3DTEXTURE9 GetD3DTexture() const { return m_pTexture; }

	void LoadFromFile(const std::string& fileName, D3DCOLOR colorTransparent = D3DCOLOR_XRGB(0, 0, 0));

	int GetWidth()  const	{ return m_info.Width; }
	int GetHeight() const	{ return m_info.Height; }
	
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
    D3DXIMAGE_INFO		m_info;
};


typedef	std::vector<Texture*>	Textures;


#endif	// #ifndef __TEXTURE_H
