#include "ConsoleManager.h"

#include <chrono>

#include "InputManager.h"

const float ConsoleManager::MS_PER_UPDATE = 33.3f / 1000.0f;

ConsoleManager::ConsoleManager() : swapToSecondaryBuffer(true) {
	outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	inHandle = GetStdHandle(STD_INPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(outHandle, &csbi)) {
		width = csbi.srWindow.Right + 1;
		height = csbi.srWindow.Bottom + 1;

		foregroundColor = csbi.wAttributes & 0x0F;
		backgroundColor = csbi.wAttributes & 0xF0;

		rectSize = csbi.dwSize;
	}

	GetConsoleCursorInfo(outHandle, &cursorInfo);

	currentBuffer = secondaryBuffer = CreateConsoleScreenBuffer(GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
	SetConsoleScreenBufferSize(secondaryBuffer, csbi.dwMaximumWindowSize);
	SetConsoleScreenBufferSize(outHandle, csbi.dwMaximumWindowSize);
}

void ConsoleManager::run() {
	/*
	auto previous = std::chrono::high_resolution_clock::now();
	double lag = 0.0;
	while (!shouldClose()) {
		auto current = std::chrono::high_resolution_clock::now();
		double elapsed = std::chrono::duration<double, std::milli>(current - previous).count();
		previous = current;
		lag += elapsed;

		readInput();

		while (lag >= MS_PER_UPDATE) {
			update();
			lag -= MS_PER_UPDATE;
		}

		render(lag / MS_PER_UPDATE);

		swapBuffer();
	}
	*/

	auto previous = std::chrono::high_resolution_clock::now();
	double lag = 0.0f;
	while(!shouldClose()) {
		auto current = std::chrono::high_resolution_clock::now();
		double deltaTime = std::chrono::duration<double, std::milli>(current - previous).count();
		previous = current;
		lag += deltaTime;

		readInput();

		while(lag >= MS_PER_UPDATE) {
			update();
			lag -= MS_PER_UPDATE;
		}

		render(lag / MS_PER_UPDATE);

		swapBuffer();
	}
}

void ConsoleManager::setTitle(const std::wstring& title) const {
	SetConsoleTitleW(title.c_str());
}

void ConsoleManager::setForegroundColor(uint8 color) {
	foregroundColor = color;

	setConsoleColor();
}

uint8 ConsoleManager::getForegroundColor() const {
	return foregroundColor;
}

void ConsoleManager::setBackgroundColor(uint8 color, bool clearScreen) {
	backgroundColor = color;

	setConsoleColor();
	if (clearScreen) {
		clear();
	}
}

uint8 ConsoleManager::getBackgroundColor() const {
	return backgroundColor;
}

void ConsoleManager::setCursorVisibilty(bool visibility) {
	cursorInfo.bVisible = visibility;

	SetConsoleCursorInfo(outHandle, &cursorInfo);
	SetConsoleCursorInfo(secondaryBuffer, &cursorInfo);
}

bool ConsoleManager::getCursorVisibility() const {
	return cursorInfo.bVisible == 1;
}

COORD ConsoleManager::getCursorPosition() const {
	COORD retval = {0, 0};
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(currentBuffer, &csbi)) {
		retval = csbi.dwCursorPosition;
	}

	return std::move(retval);
}

void ConsoleManager::setCursorPosition(int16 x, int16 y) const {
	setCursorPosition({ x, y });
}

void ConsoleManager::setCursorPosition(COORD coord) const {
	SetConsoleCursorPosition(currentBuffer, coord);
}

void ConsoleManager::scrollByAbsolute(HANDLE consoleBuffer, SHORT rows) {
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	SMALL_RECT srctWindow;

	// Get the current screen buffer size and window position. 

	if (!GetConsoleScreenBufferInfo(currentBuffer, &csbiInfo)) {
		printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
		return;
	}

	srctWindow = csbiInfo.srWindow;

	// Check whether the window is too close to the screen buffer top

	if (srctWindow.Top >= rows) {
		srctWindow.Top -= rows;     // move top up
		srctWindow.Bottom -= rows;  // move bottom up

		if (!SetConsoleWindowInfo(
			consoleBuffer,     // screen buffer handle 
			TRUE,             // absolute coordinates 
			&srctWindow))     // specifies new location 
		{
			printf("SetConsoleWindowInfo (%d)\n", GetLastError());
			return;
		}

		return;
	} else {
		printf("\nCannot scroll; the window is too close to the top.\n");
		return;
	}
}

uint16 ConsoleManager::getWidth() const {
	return width;
}

uint16 ConsoleManager::getHeight() const {
	return height;
}

void ConsoleManager::clear() const {
	DWORD count;
	WORD size = rectSize.X * rectSize.Y;
	WORD color = ((backgroundColor & 0x0F) << 4) | (foregroundColor & 0x0F);

	FillConsoleOutputCharacter(currentBuffer, ' ', size, { 0, 0 }, &count);
	FillConsoleOutputAttribute(currentBuffer, color, size, { 0, 0 }, &count);
	SetConsoleCursorPosition(currentBuffer, { 0, 0 });
}

void ConsoleManager::write(const std::wstring& text) {
	DWORD written;
	WriteConsoleW(currentBuffer, text.c_str(), text.length(), &written, nullptr);
}

void ConsoleManager::write(const std::wstring& text, uint8 foregroundColor) {
	this->foregroundColor = foregroundColor;
	setConsoleColor(); // Save old color and apply new one
	write(text); // Write text with the new color
}

void ConsoleManager::write(const std::wstring& text, uint8 foregroundColor, uint8 backgroundColor) {
	this->foregroundColor = foregroundColor;
	this->backgroundColor = backgroundColor;
	setConsoleColor(); // Save old color and apply new one

	write(text); // Write text with the new color
}

void ConsoleManager::write(int16 x, int16 y, const std::wstring& text) {
	setCursorPosition(x, y);
	write(text);
}

void ConsoleManager::write(int16 x, int16 y, const std::wstring& text, uint8 foregroundColor) {
	setCursorPosition(x, y);
	write(text, foregroundColor);
}
void ConsoleManager::write(int16 x, int16 y, const std::wstring& text, uint8 foregroundColor, uint8 backgroundColor) {
	setCursorPosition(x, y);
	write(text, foregroundColor, backgroundColor);
}

void ConsoleManager::setConsoleColor() const {
	WORD wColor = ((backgroundColor & 0x0F) << 4) + (foregroundColor & 0x0F);
	SetConsoleTextAttribute(outHandle, wColor);
	SetConsoleTextAttribute(secondaryBuffer, wColor);
}

void ConsoleManager::readInput() {
	DWORD eventCount;
	GetNumberOfConsoleInputEvents(inHandle, &eventCount);

	INPUT_RECORD event;
	DWORD eventReaded;
	while (eventCount-- > 0) {
		ReadConsoleInput(inHandle, &event, 1, &eventReaded); // Read input event
		if (eventReaded <= 0) {
			break;
		}

		if (event.EventType != KEY_EVENT) {
			continue;
		}

		InputManager::handleEvent(event.Event.KeyEvent.wVirtualKeyCode, event.Event.KeyEvent.bKeyDown ? KeyAction::Press : KeyAction::Release);
	}
}

void ConsoleManager::swapBuffer() {
	currentBuffer = !swapToSecondaryBuffer ? secondaryBuffer : outHandle;
	clear();

	SetConsoleActiveScreenBuffer(swapToSecondaryBuffer ? secondaryBuffer : outHandle);
	swapToSecondaryBuffer = !swapToSecondaryBuffer;
}
