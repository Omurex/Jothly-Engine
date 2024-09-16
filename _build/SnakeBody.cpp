#include "SnakeBody.h"
#include "Math.h"


namespace jothly
{
	void SnakeBody::UpdateLocation()
	{
		if (parent != nullptr)
		{
			Vector2 vec = (owner->transform.pos - parent->prevFramePosition);
			float mag = vec.GetMagnitude();

			if (Approx(mag, 0) == false)
			{
				Vector2 dir = vec / mag;
			
 				owner->transform.pos = parent->prevFramePosition + (dir * radius) + (dir * parent->radius);
			}
		}

		if(child != nullptr) child->UpdateLocation();
		prevFramePosition = owner->transform.pos;
	}


	void SnakeBody::DrawObject()
	{
		GetOwner()->Draw();
		if (child != nullptr) child->DrawObject();
	}


	bool SnakeBody::IsOverlappingBody(Vector2 pos, float radius)
	{
		if ((pos - owner->transform.pos).GetMagnitude() < radius + this->radius)
		{ 
			return true;
		}

		if (child != nullptr)
		{
			return child->IsOverlappingBody(pos, radius);
		}

		return false;
	}

	
	bool SnakeBody::AddChild(SnakeBody* _child)
	{
		child = _child;
		return true;
	}


	std::string SnakeBody::CreateVisualRepresentationString()
	{
		std::string ret = "";
		ret += std::to_string(owner->transform.pos.x) + "|" + std::to_string(owner->transform.pos.y);

		if (child != nullptr)
		{
			ret += "|" + child->CreateVisualRepresentationString();
		}

		return ret;
	}


	ComponentID jothly::SnakeBody::GetID() const
	{
		return ComponentID::SNAKE_BODY;
	}
}
