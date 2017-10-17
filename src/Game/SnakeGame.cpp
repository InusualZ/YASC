#include "SnakeGame.h"

#include "..\Engine\InputManager.h"

SnakeGame::SnakeGame() : ConsoleManager(), minX(0), minY(5), maxX(getWidth()), maxY(getHeight() - 5), 
	snake(nullptr), food(nullptr), gameStarted(false), quit(false), score(0) {
	setTitle(L"Snake Game");
	setCursorVisibilty(false);

	std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void SnakeGame::update() {
	if (!gameStarted) {
		if (InputManager::isKeyPressed(Key::SPACE)) {
			// Start Game
			gameStarted = true;
			snake = new Snake(getRandomPosition());
			food = new Food(getRandomPosition());
		} else if (InputManager::isKeyPressed(Key::ESC)) {
			// Quit game
			quit = true;
		}

		return;
	}

	if (gameOver) {
		if (InputManager::isKeyPressed(Key::SPACE)) {
			// Continue to Start Game Screen;
			gameStarted = false;
			gameOver = false;
			score = 0;
		} else if (InputManager::isKeyPressed(Key::ESC)) {
			// Quit game
			quit = true;
		}
		return;
	} 

	// Update Snake AI
	snake->onUpdate();

	// Check if snake is out of bound
	Vector2 snakePosition = snake->getPosition();
	if (snakePosition.x == minX) {
		snakePosition.x = maxX - 2;
	}
	else if (snakePosition.x == maxX - 1) {
		snakePosition.x = minX + 2;
	}

	if (snakePosition.y == minY) {
		snakePosition.y = maxY - 2;
	}
	else if (snakePosition.y == maxY - 1) {
		snakePosition.y = minY + 2;
	}

	snake->setPosition(snakePosition);

	// Chech if the game is over
	if (snake->isOver()) {
		gameOver = true;
		delete snake;
		delete food;
		return;
	}

	// Check if the snake is eating the food
	if (snake->isColliding(*food)) {
		++score;
		snake->addTail();
		food->setPosition(SnakeGame::getRandomPosition());
	}
}

void SnakeGame::render(double deltaTime) {
	writeTemplate();

	if (!gameStarted) {
		write(getWidth() / 2 - 25, getHeight() / 2, L"Start Game [Space] - Quit [Esc]", WHITE);
		return;
	}

	if (gameOver) {
		write(getWidth() / 2 - 25, getHeight() / 2 - 2, L"Score: " + std::to_wstring(score), WHITE);
		write(getWidth() / 2 - 25, getHeight() / 2 + 1, L"Game Over!", WHITE);
		write(getWidth() / 2 - 25, getHeight() / 2 + 2, L"[Space]", WHITE);
		return;
	}

	snake->onRender(*this);
	food->onRender(*this);

	write(getWidth() / 2 - 15, 3, L"Score: " + std::to_wstring(score), WHITE);
}

bool SnakeGame::shouldClose() {
	return quit;
}

void SnakeGame::writeTemplate() {
	for (int16 x = minX; x < maxX; ++x) {
		if (x == minX || x == maxX - 1) {
			for (int16 y = minY; y < maxY; ++y) {
				write(x, y, L"*", YELLOW);
			}
		} else if (x > minX && x < maxX - 1) {
			write(x, minY, L"*", YELLOW);
			write(x, maxY - 1, L"*", YELLOW);
		}
	}
}

void SnakeGame::writeChar(const Vector2& position, const std::wstring& text) {
	write(position.x, position.y, text);
}

void SnakeGame::writeChar(const Vector2& position, const std::wstring& text, Color color) {
	write(position.x, position.y, text, static_cast<uint8>(color));
}

int16 SnakeGame::getRandomNumber(int16 min, int16 max) {
	return static_cast<int16>(((std::rand() % max) + min));
}

Vector2 SnakeGame::getRandomPosition() {
	auto clamp = [](int16 value, int16 minVal, int16 maxVal) {
		return max(minVal, min(value, maxVal));
	};

	auto x = clamp(getRandomNumber(0, getWidth()), minX + 1, maxX - 1);
	auto y = clamp(getRandomNumber(0, getHeight()), minY + 1, maxY - 2);
	return {  x, y };
}