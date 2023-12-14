#include "GameObject.h"


void GameObject::Update()
{
	for (auto comp : components)
	{
		comp.second->Update();
	}
}


void GameObject::Draw()
{
	for (auto comp : components)
	{
		comp.second->Draw();
	}
}