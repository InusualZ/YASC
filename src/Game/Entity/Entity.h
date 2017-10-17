#pragma once

#include "..\Direction.h"
#include "..\Renderer.h"
#include "..\Vector2.h"

class Entity {
protected:
	Vector2 position;
	Vector2 lastPosition;
	Direction direction;

public:
	Entity(const Vector2& position);
	
	const Vector2& getPosition() const;

	void setPosition(const Vector2& newPosition);

	Direction getFacingDirection() const;

	bool isColliding(const Entity& other) const;

	virtual void onUpdate() = 0;

	virtual void onRender(Renderer& renderer) = 0;
};