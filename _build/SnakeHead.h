#pragma once
#include "Vector2.h"
#include "Component.h"
#include "SnakeBody.h"
#include "Texture.h"
#include "InputCodes.hpp"


namespace jothly
{
	class SnakeHead : public SnakeBody
	{
		Vector2 vel = Vector2(0);

		float accelerationSpeed = 5;

		SnakeBody* end = nullptr;

		Texture* headTexture = nullptr;
		Texture* bodyTexture = nullptr;

		bool debugWASDControls = true;

		
		public:
		SnakeHead(GameObject* _owner) : SnakeBody(_owner) {}

		SnakeHead* Init(Texture* _headTexture, Texture* _bodyTexture, bool _debugWASDControls, float _radius = 8, float _accelerationSpeed = 5);

		void Update(float dt) override;
		void Draw() override;

		void UpdateVelocityFromInput(Vector2 input, float dt);

		void GrowSnake();

		bool AddChild(SnakeBody* _child) override;


		void PerformActionsFromInput(KeyCode spawnBodyKey, KeyCode up, KeyCode down, KeyCode left, KeyCode right, float dt);
		void HandleInput(float dt);


		bool CheckIfHeadCollidingWithSnake(SnakeHead* head);

		// Inherited via Component
		ComponentID GetID() const override;
	};
}