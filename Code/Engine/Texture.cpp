#include "Texture.h"
#include "Engine.h"
#include <cassert>


Texture::Texture(const char* szFileName, D3DCOLOR colorTransparent) : m_pTexture(nullptr)
{
	if (szFileName)
	{
		LoadFromFile(szFileName, colorTransparent);
	}
}

Texture::~Texture()
{
	if (m_pTexture)
	{
		m_pTexture->Release();
	}
}


void Texture::LoadFromFile(const char* szFileName, D3DCOLOR colorTransparent)
{
	if (D3DXGetImageInfoFromFile(szFileName, &m_info) != D3D_OK)
	{
		Engine::LogError("Couldn't get image information from file %s.");
		assert(false);
		return;
	}

	D3DXCreateTextureFromFileEx( 
		g_pD3DDevice,			// Direct3D device object
		szFileName,				// bitmap filename
		m_info.Width,			// bitmap image width
		m_info.Height,			// bitmap image height
		1,						// mip-map levels (1 for no chain)
		D3DPOOL_DEFAULT,		// the type of surface (standard)
		D3DFMT_UNKNOWN,			// surface format (default)
		D3DPOOL_DEFAULT,		// memory class for the texture
		D3DX_DEFAULT,			// image filter
		D3DX_DEFAULT,			// mip filter
		colorTransparent,		// color key for transparency
		&m_info,				// bitmap file info (from loaded file)
		nullptr,				// color palette
		&m_pTexture				// destination texture
	);
}
