#include "SnakeHead.h"
#include "Input.h"
#include "SpriteRenderer.h"
#include "Math.h"

#include <iostream>


namespace jothly
{
	SnakeHead* SnakeHead::Init(Texture* _headTexture, Texture* _bodyTexture, bool _debugWASDControls, float _radius, float _accelerationSpeed)
	{
		headTexture = _headTexture; 
		bodyTexture = _bodyTexture;
		radius = _radius;
		accelerationSpeed = _accelerationSpeed;
		end = this; 

		debugWASDControls = _debugWASDControls;

		GetOwner()->CreateComponent<SpriteRenderer>()->Init(headTexture);
		prevFramePosition = owner->transform.pos;

		return this;
	}


	void SnakeHead::Update(float dt)
	{
		HandleInput(dt);
		owner->transform.pos += vel;
		UpdateLocation();
		
		//if (CheckIfCollidingWithSnake(this)) std::cout << "COLLIDING" << std::endl;
		
	}

	void SnakeHead::Draw()
	{
		if (child != nullptr) child->DrawObject();
	}


	void SnakeHead::GrowSnake()
	{
		GameObject* newBody = new GameObject("SnakeBody", end->GetOwner()->transform.pos);
		newBody->CreateComponent<SpriteRenderer>()->Init(bodyTexture);
		SnakeBody* body = newBody->CreateComponent<SnakeBody>();
		AddChild(body);
	}


	bool SnakeHead::AddChild(SnakeBody* _child)
	{
		if(Approx(vel, 0)) return false; // Don't add child of moving too slow, otherwise may spawn on top of head

		bool result = true;

		if (end != this)
		{
			result = end->AddChild(_child);
		}
		else
		{
			child = _child;
		}

		_child->Init(radius, end);
		end = _child;

		return result;
	}


	void SnakeHead::PerformActionsFromInput(KeyCode spawnBodyKey, KeyCode up, KeyCode down, KeyCode left, KeyCode right, float dt)
	{
		/*if (Input::GetKeyJustPressed(spawnBodyKey))
		{
			GameObject* newBody = new GameObject("SnakeBody", end->GetOwner()->transform.pos);
			newBody->CreateComponent<SpriteRenderer>()->Init(bodyTexture);
			SnakeBody* body = newBody->CreateComponent<SnakeBody>();
			AddChild(body);
		}*/


		if (Input::GetKeyDown(up))
		{
			vel += Vector2(0, -accelerationSpeed) * dt;
		}

		if (Input::GetKeyDown(down))
		{
			vel += Vector2(0, accelerationSpeed) * dt;
		}

		if (Input::GetKeyDown(left))
		{
			vel += Vector2(-accelerationSpeed, 0) * dt;
		}

		if (Input::GetKeyDown(right))
		{
			vel += Vector2(accelerationSpeed, 0) * dt;
		}

	}


	void SnakeHead::HandleInput(float dt)
	{
		if (debugWASDControls)
		{
			PerformActionsFromInput(KeyCode::E, KeyCode::W, KeyCode::S, KeyCode::A, KeyCode::D, dt);
		}
		else
		{
			PerformActionsFromInput(KeyCode::U, KeyCode::I, KeyCode::K, KeyCode::J, KeyCode::L, dt);
		}
	}


	bool SnakeHead::CheckIfHeadCollidingWithSnake(SnakeHead* head) // Note: Heads can't collide
	{
		if (head == this) // Don't collide with immediate child
		{
			if (child != nullptr && child->child != nullptr)
			{
				return child->child->IsOverlappingBody(head->GetOwner()->transform.pos, head->radius);
			}

			return false;
		}

		if (head->child != nullptr) return head->child->IsOverlappingBody(GetOwner()->transform.pos, radius);

		return false;
	}


	ComponentID SnakeHead::GetID() const
	{
		return ComponentID::SNAKE_HEAD;
	}
}
