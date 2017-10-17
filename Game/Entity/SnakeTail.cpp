#include "SnakeTail.h"

SnakeTail::SnakeTail(const Vector2& position) : Entity(position), child(nullptr) {
	lastPosition = position;
}

SnakeTail::~SnakeTail() {
	delete child;
}

void SnakeTail::addChild() {
	if (child == nullptr) {
		child = new SnakeTail(lastPosition);
	} else {
		child->addChild();
	}
}

bool SnakeTail::checkCollision(const Vector2& entityPosition) {
	if (position == entityPosition) {
		return true;
	}

	if (child != nullptr && child->checkCollision(entityPosition)) {
		return true;
	}

	return false;
}

void SnakeTail::moveTo(const Vector2& newPosition) {
	if (child != nullptr) {
		child->moveTo(position);
	}

	setPosition(newPosition);
}

void SnakeTail::onUpdate() {

}

void SnakeTail::onRender(Renderer& renderer) {
	renderer.writeChar(position, L"o", DARK_GREEN);
	
	if (child != nullptr) {
		child->onRender(renderer);
	}
}