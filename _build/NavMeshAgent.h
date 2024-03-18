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

		std::vector<Vector2> currentPath;
		Vector2 destination;

		bool positionLocked;

		protected:

		NavMeshAgent(GameObject* _owner) : Component(_owner) { Init(); destination = owner->transform.pos; }
		~NavMeshAgent() {}


		public:
		NavMeshAgent* Init(NavMesh* _navMesh = nullptr, float _speed = 20, float _pathRefreshRate = .1f, bool _positionLocked = false);

		void SetDestination(Vector2 _destination) { destination = _destination; }
		bool UpdatePathToDestination(); // true if path valid, false if not

		void SetSpeed(float _speed) { speed = _speed; }
		void SetPathRefreshRate(float _pathRefreshRate = std::numeric_limits<float>::max()) { pathRefreshRate = _pathRefreshRate; }


		// Inherited via Component
		ComponentID GetID() const override;
	};
}