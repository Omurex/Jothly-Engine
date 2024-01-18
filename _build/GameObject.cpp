#include "GameObject.h"


namespace jothly
{
    GameObject::~GameObject()
    {
		DestroyAllComponents();
    }


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
		delete it->second;

		return true;
	}


	void GameObject::DestroyAllComponents()
	{
		for (auto it : components)
		{
			delete it.second;
		}

		components.clear();
	}
}