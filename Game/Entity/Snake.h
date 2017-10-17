#pragma once

#include "Entity.h"

class SnakeTail;

class Snake final : public Entity {
private:
	static const int RENDER_STEP = 3;

	SnakeTail* tail;

	int canMove = 0;

	bool gameOver;

public:
	Snake(const Vector2& position);
	~Snake();

	void onUpdate() override;

	void onRender(Renderer& renderer) override;

	void addTail();

	bool isOver() const;
};