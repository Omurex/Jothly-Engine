#pragma once

#include <unordered_map>

#include "raylib.h"
#include "ComponentID.hpp"
#include "Component.h"

class Component;

class GameObject
{
	public:

	Transform transform;
	std::unordered_map<ComponentID, Component*> components;

	void Update();
	void Draw();
};