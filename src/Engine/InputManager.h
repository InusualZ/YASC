#pragma once

#include <array>

#include "..\Common.h"

enum Key {
	UNKNOWN,
	UP,
	DOWN,
	LEFT,
	RIGHT,
	ESC,
	SPACE,
	COUNT
};

enum class KeyAction {
	Press,
	Release
};

class InputManager {
private:
	static std::array<bool, Key::COUNT> keys;

public:
	static bool isKeyPressed(Key key);

	static void handleEvent(uint16 key, KeyAction action);

private:
	static Key translateKeyCode(uint16 key);
};