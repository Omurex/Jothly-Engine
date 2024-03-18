#pragma once

#include "Component.h"
#include "Navmesh.h"


namespace jothly
{
	class NavMeshAgent : public Component
	{
		friend class GameObject;

		NavMesh* navMesh;

		float speed;
		float pathRefreshRate; // Every time pathRefreshRate seconds pass, update path
		float pathPointCheckRadius;

		std::vector<Vector2> currentPath;
		Vector2 destination;

		bool navigating;
		int currentPathIndex = -1;

		void Update(float dt) override;

		protected:

		NavMeshAgent(GameObject* _owner) : Component(_owner) { Init(); destination = owner->transform.pos; }
		~NavMeshAgent() {}


		public:
		NavMeshAgent* Init(NavMesh* _navMesh = nullptr, float _speed = 40, float _pathRefreshRate = .1f, 
				float _pathPointCheckRadius = 3.0f, bool _positionLocked = false);

		void SetDestination(Vector2 _destination) { destination = _destination; UpdatePathToDestination(); }
		bool UpdatePathToDestination(); // true if path valid, false if not

		void SetSpeed(float _speed) { speed = _speed; }
		void SetPathRefreshRate(float _pathRefreshRate = std::numeric_limits<float>::max()) { pathRefreshRate = _pathRefreshRate; }

		void MoveTowardsPoint(Vector2 point, float dt);

		void TravelPath(float dt);

		// Inherited via Component
		ComponentID GetID() const override;
	};
}