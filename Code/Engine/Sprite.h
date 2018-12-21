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

	virtual void Reset();

	void Animate();
	void Render() const;

	Vector2 GetPos() const { return m_pos; }
	void SetPos(const Vector2& pos) { m_pos = pos; }
	void SetPos(float x, float y) { m_pos.x = x; m_pos.y = y; }

	void SetFrameTimer(int iFrameTimer) { m_iFrameTimer = iFrameTimer; }

	int  GetAnimationFrames() const { return m_numAnimationFrames; }
	void SetAnimationFrames(int numAnimationFrames) { m_numAnimationFrames = numAnimationFrames; }

	int GetAnimationFrame() const { return m_iAnimationFrame; }
	void SetAnimationFrame(int iAnimationFrame)	{ m_iAnimationFrame = iAnimationFrame; }

	void SetColor(Engine::EColor eColor);
	void SetAlpha(unsigned char alpha) { m_color &= 0xFFFFFF; m_color |= ((alpha & 0xFF) << 24); }

	std::shared_ptr<Texture> GetTexture() const { return m_pTexture; }
	void SetTexture(std::shared_ptr<Texture> pTexture, int nWidth = 0, int nHeight = 0, int nColumns = 0);

	int	GetWidth()  const { return m_nWidth; }
	void SetWidth(int nWidth) { m_nWidth = nWidth; }

	int	GetHeight() const { return m_nHeight; }
	void SetHeight(int nHeight) { m_nHeight = nHeight; }

	bool HasTexture() const { return !m_pTexture->IsEmpty(); }

	bool Overlaps(std::shared_ptr<Sprite> pSpriteOther) const;

protected:
	Vector2		m_pos;

	std::shared_ptr<Texture>	m_pTexture;

	int	m_nWidth;
	int	m_nHeight;

	// Animation
	long int	m_nFrameIDStart;
	int			m_iFrameTimer;
	int			m_numAnimationColumns;
	int			m_iAnimationFrame;
	int			m_numAnimationFrames;

private:
	D3DCOLOR	m_color;
};
