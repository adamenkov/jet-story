#include "Sprite.h"
#include "Engine.h"


Sprite::Sprite() :
	m_pos(ZERO),
	m_pTexture(nullptr),
	m_nWidth(0),
	m_nHeight(0),
	m_nFrameIDStart(0),
	m_nFrameTimer(0),
	m_numAnimationColumns(1),
	m_nAnimationFrame(0),
	m_numAnimationFrames(0),
	m_color(0xFFFFFFFF)
{
}


void Sprite::Reset()
{
	m_nAnimationFrame = 0;
}


void Sprite::Animate()
{
	if (m_nFrameTimer > 0)
	{
		long int nFrameID = Engine::GetFrameID();

		if (nFrameID >= m_nFrameIDStart + m_nFrameTimer)
		{
			m_nFrameIDStart = nFrameID;

			++m_nAnimationFrame;
			if (m_nAnimationFrame >= m_numAnimationFrames)
			{
				m_nAnimationFrame = 0;
			}
		}
	}
}


void Sprite::Render() const
{
	int x = (m_nAnimationFrame % m_numAnimationColumns) * m_nWidth;
	int y = (m_nAnimationFrame / m_numAnimationColumns) * m_nHeight;
	RECT srcRect = { x, y, x + m_nWidth, y + m_nHeight };

	D3DXMATRIX matrix;
	D3DXVECTOR2 scale(1.f, 1.f);
	D3DXVECTOR2 center(.5f * m_nWidth, .5f * m_nHeight);

	// To avoid brightness artifacts, draw only at integer coordinates
	D3DXVECTOR2 trans(static_cast<FLOAT>(static_cast<int>(m_pos.x)), static_cast<FLOAT>(static_cast<int>(m_pos.y)));

	D3DXMatrixTransformation2D(&matrix, nullptr, 0, &scale, &center, 0.f, &trans);
	g_pDirect3DXSprite->SetTransform(&matrix);

	g_pDirect3DXSprite->Draw(m_pTexture->GetDirect3DTexture(), &srcRect, nullptr, nullptr, m_color);
}


void Sprite::SetColor(Engine::EColor eColor)
{
	static const D3DCOLOR aZXColors[] = {
		D3DCOLOR_XRGB(  0,   0,   0),	// Black
		D3DCOLOR_XRGB(  0,   0, 200),	// Blue
		D3DCOLOR_XRGB(200,   0,   0),	// Red
		D3DCOLOR_XRGB(200,   0, 200),	// Magenta

		D3DCOLOR_XRGB(  0, 200,   0),	// Green
		D3DCOLOR_XRGB(  0, 200, 200),	// Cyan
		D3DCOLOR_XRGB(200, 200,   0),	// Yellow
		D3DCOLOR_XRGB(200, 200, 200),	// Grey

		D3DCOLOR_XRGB(  0,   0,   0),	// Light black
		D3DCOLOR_XRGB(  0,   0, 248),	// Light blue
		D3DCOLOR_XRGB(248,   0,   0),	// Light red
		D3DCOLOR_XRGB(248,   0, 248),	// Light magenta

		D3DCOLOR_XRGB(  0, 248,   0),	// Light green
		D3DCOLOR_XRGB(  0, 248, 248),	// Light cyan
		D3DCOLOR_XRGB(248, 248,   0),	// Light yellow
		D3DCOLOR_XRGB(248, 248, 248),	// White
	};

	m_color = aZXColors[eColor];
}


void Sprite::SetTexture(std::shared_ptr<Texture> pTexture, int nWidth /*= 0*/, int nHeight /*= 0*/, int nColumns /*= 0*/)
{
	m_pTexture = pTexture;

	m_nWidth  = (nWidth  > 0) ? nWidth  : m_pTexture->GetWidth();
	m_nHeight = (nHeight > 0) ? nHeight : m_pTexture->GetHeight();

	m_numAnimationColumns = (nColumns > 0) ? nColumns : m_pTexture->GetWidth() / m_nWidth;
	m_numAnimationFrames = m_numAnimationColumns * (m_pTexture->GetHeight() / m_nHeight);
}


bool Sprite::Overlaps(const Sprite* pSpriteOther) const
{
	LONG left = static_cast<LONG>(m_pos.x);
	LONG top  = static_cast<LONG>(m_pos.y);
	RECT rect = { left, top, left + m_nWidth, top + m_nHeight };
	
	Vector2 posOther = pSpriteOther->GetPos();
	left = static_cast<LONG>(posOther.x);
	top  = static_cast<LONG>(posOther.y);
	RECT rectOther = { left, top, left + pSpriteOther->GetWidth(), top + pSpriteOther->GetHeight() };

	RECT rectCollision;
	return (IntersectRect(&rectCollision, &rect, &rectOther) != FALSE);
}
