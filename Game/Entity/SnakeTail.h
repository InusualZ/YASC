#pragma once

#include "Entity.h"

class SnakeTail final : public Entity {
private:
	SnakeTail* child;

public:
	SnakeTail(const Vector2& position);
	~SnakeTail();

	void addChild();

	bool checkCollision(const Vector2& entityPosition);

	void moveTo(const Vector2& newPosition);

	void onUpdate() override;

	void onRender(Renderer& renderer) override;
};