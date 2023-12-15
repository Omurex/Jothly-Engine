#include "Component.h"
#include <stdexcept>
#include <string>


Component::Component(GameObject* _owner) : owner(_owner), enabled(true)
{
	// Would like to put id into debug string but not worth it atm since we'd have to
	// give this constructor an extra parameter since the abstract function GetID can't be called from here
	if (owner == nullptr) // Owner doesn't exist
	{
		std::string errorStr = "Owner of component cannot be null!";
		errorStr += "\n";

		throw std::invalid_argument(errorStr);
	}

	owner = _owner;
}
