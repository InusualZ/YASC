#include "Snake.h"

#include "../../Engine/InputManager.h"

#include "SnakeTail.h"


Snake::Snake(const Vector2& position) : Entity(position), tail(nullptr), gameOver(false) {
	direction = Direction::Undefined;
}

Snake::~Snake() {
	delete tail;
}

void Snake::onUpdate() {
	// Detect Key presses
	if (InputManager::isKeyPressed(Key::UP)) {
		direction = Direction::North;
	} else if (InputManager::isKeyPressed(Key::DOWN)) {
		direction = Direction::South;
	} else if (InputManager::isKeyPressed(Key::LEFT)) {
		direction = Direction::West;
	} else if (InputManager::isKeyPressed(Key::RIGHT)) {
		direction = Direction::East;
	}

	if (canMove != RENDER_STEP) {
		return;
	}

	canMove = 0;

	// Act based on direction headed
	Vector2 oldPosition = position;
	if (direction == Direction::North) {
		position.y -= 1;
	} else if (direction == Direction::South) {
		position.y += 1;
	} else if (direction == Direction::West) {
		position.x -= 1;
	} else if (direction == Direction::East) {
		position.x += 1;
	}

	if (tail != nullptr) {
		if (!tail->checkCollision(position)) {
			tail->moveTo(oldPosition);
		} else {
			gameOver = true;
		}
	}
}

void Snake::onRender(Renderer& renderer) {
	if (direction == Direction::North) {
		renderer.writeChar(position, L"^", Color::GREEN);
	} else if (direction == Direction::South) {
		renderer.writeChar(position, L"V", Color::GREEN);
	} else if (direction == Direction::East) {
		renderer.writeChar(position, L">", Color::GREEN);
	} else if (direction == Direction::West) {
		renderer.writeChar(position, L"<", Color::GREEN);
	} else {
		renderer.writeChar(position, L"X", Color::DARK_GREEN);
	}

	canMove = ((canMove++) % RENDER_STEP);

	if (tail != nullptr) {
		tail->onRender(renderer);
	}
}

void Snake::addTail() {
	if (tail != nullptr) {
		tail->addChild();
	} else {
		// Calculate tail position
		Vector2 tailPosition = position;
		if (direction == Direction::North) {
			tailPosition.y += 1;
		} else if (direction == Direction::South) {
			tailPosition.y -= 1;
		} else if (direction == Direction::East) {
			tailPosition.x -= 1;
		} else if (direction == Direction::West) {
			tailPosition.x += 1;
		} else { 
			// If for some reason the Direction is undefined return and don't add the tail
			return;
		}

		tail = new SnakeTail(tailPosition);
	}
}

bool Snake::isOver() const {
	return gameOver;
}