#include "SnakeBody.h"


namespace jothly
{
	void SnakeBody::UpdateLocation()
	{
		if(parent != nullptr) owner->transform.pos = parent->prevFramePosition;
		if(child != nullptr) child->UpdateLocation();
		prevFramePosition = owner->transform.pos;
	}


	void SnakeBody::DrawObject()
	{
		GetOwner()->Draw();
		if (child != nullptr) child->DrawObject();
	}

	
	void SnakeBody::AddChild(SnakeBody* _child)
	{
		child = _child;
	}


	ComponentID jothly::SnakeBody::GetID() const
	{
		return ComponentID::SNAKE_BODY;
	}
}
