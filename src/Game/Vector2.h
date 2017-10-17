#pragma once

#include "..\Common.h"

class Vector2 {
public:
	int16 x, y;

public:
	Vector2();
	Vector2(int16 scalar);
	Vector2(int16 x, int16 y);


	//Math functions
	Vector2& add(int16 value);
	Vector2& add(const Vector2&);

	Vector2& substract(int16 value);
	Vector2& substract(const Vector2&);

	Vector2& multiply(int16 value);
	Vector2& multiply(const Vector2&);

	Vector2& divide(int16 value);
	Vector2& divide(const Vector2&);

	Vector2 operator+(int16);
	Vector2 operator+(const Vector2&);

	Vector2 operator-(int16);
	Vector2 operator-(const Vector2&);

	Vector2 operator*(int16);
	Vector2 operator*(const Vector2&);

	Vector2 operator/(int16);
	Vector2 operator/(const Vector2&);

	Vector2& operator+=(const Vector2&);
	Vector2& operator-=(const Vector2&);
	Vector2& operator*=(const Vector2&);
	Vector2& operator/=(const Vector2&);

	bool operator==(const Vector2&) const;
	bool operator!=(const Vector2&) const;
};