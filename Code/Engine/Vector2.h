#pragma once

#include <cmath>


enum type_zero { ZERO };

struct Vector2
{
	float x, y;

	Vector2(type_zero) : x(0.f), y(0.f) {}
	Vector2(float x, float y) : x(x), y(y) {}

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

	Vector2& operator+=(const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2& operator*=(float coeff)
	{
		x *= coeff;
		y *= coeff;
		return *this;
	}

	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
	}
	
	friend Vector2 operator*(float coeff, const Vector2& rhs)
	{
		return Vector2(coeff * rhs.x, coeff * rhs.y);
	}
};
