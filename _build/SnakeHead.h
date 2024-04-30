#pragma once
#include "Vector2.h"
#include "Component.h"
#include "SnakeBody.h"
#include "Texture.h"


namespace jothly
{
	class SnakeHead : public SnakeBody
	{
		Vector2 vel = Vector2(0);

		float accelerationSpeed = 5;

		SnakeBody* end = nullptr;

		Texture* headTexture = nullptr;
		Texture* bodyTexture = nullptr;

		
		public:
		SnakeHead(GameObject* _owner) : SnakeBody(_owner) {}

		SnakeHead* Init(Texture* _headTexture, Texture* _bodyTexture, float _radius = 8, float _accelerationSpeed = 5);

		void Update(float dt) override;
		void Draw() override;

		void AddChild(SnakeBody* _child) override;


		void HandleInput(float dt);


		bool CheckIfDead();
		bool CheckIfCollidingWithSnake(Vector2 pos, float radius);

		// Inherited via Component
		ComponentID GetID() const override;
	};
}