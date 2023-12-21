#pragma once

#include <unordered_map>
#include <string>
#include <assert.h>
#include <type_traits>
#include <stdexcept>

#include "raylib.h"
#include "ComponentID.hpp"
#include "Component.h"
#include "Constants.hpp"


namespace jothly
{
	class Component;

	class GameObject
	{
		std::unordered_map<ComponentID, Component*> components;


		public:

		std::string name;
		rlb_Transform transform;

		GameObject(std::string _name = "New Object", rlb_Transform _transform = con::rlb_DefaultTransform) : name(_name),
			transform(_transform) {}

		// Calls update and draw on all components
		void Update(float dt);
		void Draw();

		template<typename T>
		T* CreateComponent();
		Component* GetComponent(ComponentID id);
		bool DestroyComponent(ComponentID id);
	};


	template<typename T>
	inline T* GameObject::CreateComponent()
	{
		// Make sure passed in type is a component
		bool isComponent = std::is_base_of<Component, T>();
		assert(isComponent);
	
		T* specificComp = new T(this); // Will be ShapeRenderer, etc.
		Component* comp = (Component*) specificComp; // Use this for general component set up

		// Component already exists, throw error
		if (components.count(comp->GetID()) > 0)
		{
			delete comp;

			std::string errorStr = "GameObject already has component of same type!";
			errorStr += "\nGameObject Name: " + name;
			errorStr += "\nComponent ID: " + std::to_string((int) comp->GetID());
			errorStr += "\n";

			throw std::invalid_argument(errorStr);
		}

		components.insert(std::make_pair(comp->GetID(), comp));

		return specificComp;
	}
}