#pragma once

#include <string>

#include "Vector2.h"

enum Color : uint8 {
	NONE,
	DARK_BLUE,
	DARK_GREEN,
	DARK_CYAN,
	DARK_RED,
	DARK_MAGENTA,
	DARK_YELLOW,
	DARK_WHITE,
	DARK_GREY,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE

};

class Renderer {
public:
	virtual void writeChar(const Vector2& position, const std::wstring& text) = 0;

	virtual void writeChar(const Vector2& position, const std::wstring& text, Color color) = 0;
};