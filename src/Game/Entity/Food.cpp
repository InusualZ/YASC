#include "Food.h"

Food::Food(const Vector2& position) : Entity(position) {}

void Food::onUpdate() {}

void Food::onRender(Renderer& renderer) {
	renderer.writeChar(position, L"A", Color::RED);
}