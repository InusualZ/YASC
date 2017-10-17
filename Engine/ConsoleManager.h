#pragma once

#include <string>

#include <Windows.h>

#include "..\Common.h"

class ConsoleManager {
private:
	HANDLE outHandle;
	HANDLE secondaryBuffer;
	HANDLE currentBuffer;

	HANDLE inHandle;

	uint8 backgroundColor;
	uint8 foregroundColor;

	uint16 width;
	uint16 height;

	COORD rectSize;

	CONSOLE_CURSOR_INFO cursorInfo;

	bool swapToSecondaryBuffer;

public:
	static const float MS_PER_UPDATE;

public:
	ConsoleManager();

	void run();

	void setTitle(const std::wstring& title) const;

	// Would set the font color for both console buffer
	void setForegroundColor(uint8 color);

	// Would get the font color
	uint8 getForegroundColor() const;

	// Would set the background color for both console buffer
	void setBackgroundColor(uint8 color, bool clearScreen = false);

	// Would get the background color
	uint8 getBackgroundColor() const;

	// Would clear the current console buffer
	void clear() const;

	// Would set the visibility of the for both console buffer
	void setCursorVisibilty(bool visibility);

	// Would get the visibility of the cursor
	bool getCursorVisibility() const;

	// Would get the position of the cursor in the current console buffer
	COORD getCursorPosition() const;
	
	// Would set the position to the cursor for the current console buffer
	void setCursorPosition(int16 x, int16 y) const;
	void setCursorPosition(COORD coord) const;

	uint16 getWidth() const;
	uint16 getHeight() const;

	void write(const std::wstring& text);
	void write(const std::wstring& text, uint8 foregroundColor);
	void write(const std::wstring& text, uint8 foregroundColor, uint8 backgroundColor);

	void write(int16 x, int16 y, const std::wstring& text);
	void write(int16 x, int16 y, const std::wstring& text, uint8 foregroundColor);
	void write(int16 x, int16 y, const std::wstring& text, uint8 foregroundColor, uint8 backgroundColor);

public:
	virtual void update() = 0;

	virtual void render(double deltaTime) = 0;

	virtual bool shouldClose() = 0;

private:

	void scrollByAbsolute(HANDLE consoleBuffer, SHORT row);

	void setConsoleColor() const;

	void readInput();

	void swapBuffer();
};