#pragma once

#include <unordered_map>
#include <string>
#include <assert.h>
#include <type_traits>
#include <stdexcept>

#include "ComponentID.hpp"
#include "Component.h"
#include "Constants.hpp"
#include "Transform.h"


namespace jothly
{
	class Component;

	class GameObject
	{
		std::unordered_map<ComponentID, Component*> components;


		public:

		std::string name;
		Transform transform;

		GameObject(std::string _name, Transform _transform = Transform()) : name(_name),
			transform(_transform) {}

		GameObject(std::string _name = "New Object", Vector3 _pos = Vector3(0), Quaternion _rot = Quaternion(), Vector3 _scale = Vector3(1))
			: name(_name), transform(_pos, _rot, _scale) {}

		~GameObject();

		// Calls update and draw on all components
		void Update(float dt);
		void Draw();

		// TODO: Implement object pooling for components
		template<typename T>
		T* CreateComponent();
		Component* GetComponent(ComponentID id);
		bool DestroyComponent(ComponentID id);
		void DestroyAllComponents();
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