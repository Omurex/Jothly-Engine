#pragma once


#include "Component.h"


class ShapeRenderer : Component
{
	public:
	ShapeRenderer(GameObject* owner);
	
	ComponentID GetID() const override { return ComponentID::SHAPE_RENDERER; }

	void Draw() override;
};