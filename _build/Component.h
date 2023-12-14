#pragma once

#include "GameObject.h"
#include "ComponentID.hpp"

class GameObject;

class Component
{
	protected:

	GameObject* owner;


	public:

	virtual void Update() {};
	virtual void Draw() {};

	virtual ComponentID GetID() = 0;
	GameObject* GetOwner() { return owner; }
};