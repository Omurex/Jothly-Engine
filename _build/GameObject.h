#pragma once

#include <unordered_map>
#include <string>

#include "raylib.h"
#include "ComponentID.hpp"
#include "Component.h"

class Component;

class GameObject
{
	friend class Component;

	Component* RemoveComponent(ComponentID id);


	public:

	std::string name;
	Transform transform;
	std::unordered_map<ComponentID, Component*> components;

	GameObject(std::string _name = "New Object") : name(_name) {}

	// Calls update and draw on all components
	void Update(float dt);
	void Draw();

	bool RemoveAndDeleteComponent(ComponentID id);
};