#pragma once

#include <cstdio>
#include <ctime>

#include "..\Engine\ConsoleManager.h"

#include "Entity\Snake.h"
#include "Entity\Food.h"
#include "Renderer.h"

class SnakeGame : public ConsoleManager, public Renderer {
private:
	int16 minX, minY, maxX, maxY;

	Snake* snake;
	Food* food;

	bool gameStarted;
	bool gameOver;
	bool quit;

	int score;

public:
	SnakeGame();

	void update() override;

	void render(double deltaTime) override;

	bool shouldClose() override;

	void writeChar(const Vector2& position, const std::wstring& text) override;

	void writeChar(const Vector2& position, const std::wstring& text, Color color) override;

	static int16 getRandomNumber(int16 min, int16 max);

	Vector2 getRandomPosition();

private:
	void writeTemplate();
};