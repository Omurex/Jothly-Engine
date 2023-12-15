#include "Component.h"
#include <stdexcept>
#include <string>


Component::Component(GameObject* _owner, ComponentID id) : owner(_owner), enabled(true)
{
	if (owner == nullptr) // Owner doesn't exists
	{
		std::string errorStr = "Owner of component cannot be null!";
		errorStr += "\nComponent ID: " + std::to_string((int) id);
		errorStr += "\n";

		throw std::invalid_argument(errorStr);
	}

	if (owner->components.count(id) > 0) // Component already exists
	{
		std::string errorStr = "GameObject already has component of same type!";
		errorStr += "\nGameObject Name: " + owner->name;
		errorStr += "\nComponent ID: " + std::to_string((int) id);
		errorStr += "\n";

		throw std::invalid_argument(errorStr);
	}

	owner->components.insert(std::make_pair(id, this));
}
