#pragma once

#include "Entity.h"

class Food final : public Entity {
public:
	Food(const Vector2& position);

	void onUpdate() override;

	void onRender(Renderer& renderer) override;
};