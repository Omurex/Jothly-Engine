#include "GameObject.h"


namespace jothly
{
	void GameObject::Update(float dt)
	{
		for (auto comp : components)
		{
			comp.second->UpdateComponent(dt);
		}
	}


	void GameObject::Draw()
	{
		for (auto comp : components)
		{
			comp.second->DrawComponent();
		}
	}


	Component* GameObject::GetComponent(ComponentID id)
	{
		auto it = components.find(id);

		if(it == components.end()) return nullptr;

		return it->second;
	}


	bool GameObject::DestroyComponent(ComponentID id)
	{
		auto it = components.find(id);

		if(it == components.end()) return false;

		components.erase(it);

		return true;
	}
}