#ifndef __SPRITE_H
#define __SPRITE_H

#pragma once

// Don't change the order
#include "../Shared/Engine.h"
#include "Texture.h"
#include "Vector2.h"
#include <D3D9Types.h>
#include <vector>


class Sprite
{
public:
	Sprite();
	virtual ~Sprite() {}

	virtual void Reset();

	virtual void Animate();
	virtual void Render() const;

	Vector2 GetPos() const				{ return m_pos; }
	void SetPos(const Vector2& pos)	{ m_pos = pos; }
	void SetPos(float x, float y)	{ m_pos.x = x; m_pos.y = y; }

	void SetFrameTimer(int nFrameTimer)	{ m_nFrameTimer = nFrameTimer; }
	
	int  GetAnimationFrames() const { return m_nAnimationFrames; }
	void SetAnimationFrame(int nAnimationFrame)	{ m_nAnimationFrame = nAnimationFrame; }

	void SetColor(Engine::EColor eColor);
	void SetAlpha(unsigned char alpha) { m_color &= 0xFFFFFF; m_color |= ((alpha & 0xFF) << 24); }

	Texture* GetTexture() const { return m_pTexture; }
	void     SetTexture(Texture* pTexture, int nWidth = 0, int nHeight = 0, int nColumns = 0);

	int	GetWidth()  const { return m_nWidth; }
	int	GetHeight() const { return m_nHeight; }

	bool IsOK() const { return m_pTexture->GetD3DTexture() != NULL; }

	bool Overlaps(const Sprite* pSpriteOther) const;

protected:
	Vector2		m_pos;

	Texture*	m_pTexture;

	int	m_nWidth;
	int	m_nHeight;

	// Animation
	long int	m_nFrameIDStart;
	int			m_nFrameTimer;
	int			m_nAnimationColumns;
	int			m_nAnimationFrame;
	int			m_nAnimationFrames;

private:
	D3DCOLOR	m_color;
};


typedef	std::vector<Sprite*>	Sprites;


#endif	// #ifndef __SPRITE_H
