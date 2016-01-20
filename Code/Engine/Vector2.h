#ifndef __VECTOR2_H
#define __VECTOR2_H

#pragma once

#include <cmath>


enum type_zero { ZERO };

struct Vec2
{
	float x, y;

	Vec2(type_zero) : x(0.f), y(0.f) {}
	Vec2(float x, float y) : x(x), y(y) {}

	bool IsZero() const
	{
		return (x == 0.f) && (y == 0.f);
	}

	float GetLength() const
	{
		return sqrt(x*x + y*y);
	}
	
	void SetLength(float newLength)
	{
		float length = GetLength();
		if (length > 0.f)
		{
			float coeff = newLength / length;
			x *= coeff;
			y *= coeff;
		}
	}

	void Set(float newX, float newY)
	{
		x = newX;
		y = newY;
	}

	void Zero()
	{
		x = 0.f;
		y = 0.f;
	}

	Vec2& operator+=(const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vec2& operator*=(float coeff)
	{
		x *= coeff;
		y *= coeff;
		return *this;
	}

	friend Vec2 operator+(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	friend Vec2 operator-(const Vec2& lhs, const Vec2& rhs)
	{
		return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
	}
	
	friend Vec2 operator*(float coeff, const Vec2& rhs)
	{
		return Vec2(coeff * rhs.x, coeff * rhs.y);
	}

	friend Vec2 operator/(const Vec2& rhs, float denominator)
	{
		return Vec2(rhs.x / denominator, rhs.y / denominator);
	}
};


#endif	// #ifndef __VECTOR2_H
