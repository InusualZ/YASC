#include "Vector2.h"

Vector2::Vector2() : x(0), y(0) {}

Vector2::Vector2(int16 x, int16 y) : x(x), y(y) {}

Vector2::Vector2(int16 scalar) : x(scalar), y(scalar) {}

Vector2& Vector2::add(int16 value) {
	x += value;
	y += value;
	return *this;
}

Vector2& Vector2::add(const Vector2& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::substract(int16 value) {
	x -= value;
	y -= value;
	return *this;
}

Vector2& Vector2::substract(const Vector2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2& Vector2::multiply(int16 value) {
	x *= value;
	y *= value;
	return *this;
}

Vector2& Vector2::multiply(const Vector2& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

Vector2& Vector2::divide(int16 value) {
	x /= value;
	y /= value;
	return *this;
}

Vector2& Vector2::divide(const Vector2& other) {
	x /= other.x;
	y /= other.y;
	return *this;
}

Vector2 Vector2::operator+(int16 value) {
	return add(value);
}

Vector2 Vector2::operator+(const Vector2& other) {
	return add(other);
}

Vector2 Vector2::operator-(int16 value) {
	return substract(value);
}

Vector2 Vector2::operator-(const Vector2& other) {
	return substract(other);
}

Vector2 Vector2::operator*(int16 value) {
	return multiply(value);
}

Vector2 Vector2::operator*(const Vector2& other) {
	return multiply(other);
}

Vector2 Vector2::operator/(int16 value) {
	return divide(value);
}

Vector2 Vector2::operator/(const Vector2& other) {
	return divide(other);
}

Vector2& Vector2::operator+=(const Vector2& other) {
	return add(other);
}

Vector2& Vector2::operator-=(const Vector2& other) {
	return substract(other);
}

Vector2& Vector2::operator*=(const Vector2& other) {
	return multiply(other);
}

Vector2& Vector2::operator/=(const Vector2& other) {
	return divide(other);
}

bool Vector2::operator==(const Vector2& other) const {
	return x == other.x &&  y == other.y;
}

bool Vector2::operator!=(const Vector2& other) const {
	return !(*this == other);
}