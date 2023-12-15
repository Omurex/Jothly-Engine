#include "GameObject.h"

//
//Component* GameObject::RemoveComponent(ComponentID id)
//{
//	auto iter = components.find(id);
//
//	if(iter == components.end()) return nullptr;
//
//	Component* comp = iter->second;
//	components.erase(id);
//
//	return comp;
//}


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


//bool GameObject::RemoveAndDeleteComponent(ComponentID id)
//{
//	Component* comp = RemoveComponent(id);
//
//	if (comp == nullptr)
//	{
//		return false;
//	}
//	else
//	{
//		delete comp;
//		return true;
//	}
//}
