#pragma once


#include "Component.h"


class ShapeRenderer : Component
{
	ComponentID GetID() override { return ComponentID::SHAPE_RENDERER; }

	void Draw() override;
};