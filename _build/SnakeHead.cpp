#include "SnakeHead.h"
#include "Input.h"
#include "SpriteRenderer.h"

#include <iostream>


namespace jothly
{
	SnakeHead* SnakeHead::Init(Texture* _headTexture, Texture* _bodyTexture, float _radius, float _accelerationSpeed)
	{
		headTexture = _headTexture; 
		bodyTexture = _bodyTexture;
		radius = _radius;
		accelerationSpeed = _accelerationSpeed;
		end = this; 

		GetOwner()->CreateComponent<SpriteRenderer>()->Init(headTexture);
		prevFramePosition = owner->transform.pos;

		return this;
	}


	void SnakeHead::Update(float dt)
	{
		HandleInput(dt);
		owner->transform.pos += vel;
		UpdateLocation();
		
		if (CheckIfCollidingWithSnake(this)) std::cout << "COLLIDING" << std::endl;
		
	}

	void SnakeHead::Draw()
	{
		if (child != nullptr) child->DrawObject();
	}


	void SnakeHead::AddChild(SnakeBody* _child)
	{
		if (end != this)
		{
			end->AddChild(_child);
		}
		else
		{
			child = _child;
		}

		_child->Init(radius, end);
		end = _child;
		
	}


	void SnakeHead::HandleInput(float dt)
	{
		if (Input::GetKeyJustPressed(KeyCode::SPACE))
		{
			GameObject* newBody = new GameObject("SnakeBody", end->GetOwner()->transform.pos);
			newBody->CreateComponent<SpriteRenderer>()->Init(bodyTexture);
			SnakeBody* body = newBody->CreateComponent<SnakeBody>();
			AddChild(body);
		}


		if (Input::GetKeyDown(KeyCode::W))
		{
			vel += Vector2(0, -accelerationSpeed) * dt;
		}

		if (Input::GetKeyDown(KeyCode::S))
		{
			vel += Vector2(0, accelerationSpeed) * dt;
		}

		if (Input::GetKeyDown(KeyCode::D))
		{
			vel += Vector2(accelerationSpeed, 0) * dt;
		}

		if (Input::GetKeyDown(KeyCode::A))
		{
			vel += Vector2(-accelerationSpeed, 0) * dt;
		}
	}


	bool SnakeHead::CheckIfDead()
	{
		return false;
	}


	bool SnakeHead::CheckIfCollidingWithSnake(SnakeHead* head) // Note: Heads can't collide
	{
		if (head == this) // Don't collide with immediate child
		{
			if (child != nullptr && child->child != nullptr)
			{
				return child->child->IsOverlappingBody(head->GetOwner()->transform.pos, head->radius);
			}

			return false;
		}

		if (child != nullptr) return child->IsOverlappingBody(head->GetOwner()->transform.pos, head->radius);

		return false;
	}


	ComponentID SnakeHead::GetID() const
	{
		return ComponentID::SNAKE_HEAD;
	}
}
