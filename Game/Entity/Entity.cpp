#include "Entity.h"

#include <utility>

Entity::Entity(const Vector2& position_) : position(std::move(position_)), direction(Direction::North) {}

const Vector2& Entity::getPosition() const {
	return position;
}

void Entity::setPosition(const Vector2& newPosition) {
	lastPosition = position;
	position = newPosition;
}

Direction Entity::getFacingDirection() const {
	return direction;
}

bool Entity::isColliding(const Entity& entity) const {
	return position == entity.getPosition();
}