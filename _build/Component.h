#pragma once

#include "GameObject.h"
#include "ComponentID.hpp"

class GameObject;


// Note: GameObjects are always in charge of managing the deletion of created components, so 
class Component
{
	protected:

	GameObject* owner;
	bool enabled;

	Component(GameObject* _owner, ComponentID id);

	// Actual update and draw logic that does things in the game
	virtual void Update(float dt) {};
	virtual void Draw() {};


	public:

	void UpdateComponent(float dt) { if(enabled) Update(dt); };
	void DrawComponent() { if(enabled) Draw(); };

	virtual ComponentID GetID() const = 0;
	GameObject* GetOwner() { return owner; }

	bool IsEnabled() { return enabled; }
	void SetEnabled(bool _enabled) { enabled = _enabled; }
};