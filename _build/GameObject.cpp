#include "GameObject.h"


Component* GameObject::RemoveComponent(ComponentID id)
{
	auto iter = components.find(id);

	if(iter == components.end()) return nullptr;

	Component* comp = iter->second;
	components.erase(id);

	return comp;
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


bool GameObject::RemoveAndDeleteComponent(ComponentID id)
{
	Component* comp = RemoveComponent(id);

	if (comp == nullptr)
	{
		return false;
	}
	else
	{
		delete comp;
		return true;
	}
}
