#include "InputManager.h"

#include <Windows.h>

std::array<bool, Key::COUNT> InputManager::keys;

bool InputManager::isKeyPressed(Key key) {
	return keys[key];
}

void InputManager::handleEvent(uint16 keyCode, KeyAction action) {
	auto key = translateKeyCode(keyCode);

	keys[key] = (action == KeyAction::Press);
}

Key InputManager::translateKeyCode(uint16 key) {
	switch (key) {
	case VK_UP:
		return Key::UP;
		break;

	case VK_DOWN:
		return Key::DOWN;
		break;

	case VK_LEFT:
		return Key::LEFT;
		break;

	case VK_RIGHT:
		return Key::RIGHT;
		break;

	case VK_ESCAPE:
		return Key::ESC;
		break;

	case VK_SPACE:
		return Key::SPACE;
		break;
		
	default:
		return Key::UNKNOWN;
		break;
	}
}