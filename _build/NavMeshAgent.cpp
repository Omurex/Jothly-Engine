#include "NavMeshAgent.h"

namespace jothly
{
    NavMeshAgent* NavMeshAgent::Init(NavMesh* _navMesh, float _speed, float _pathRefreshRate, bool _positionLocked)
    {
        navMesh = _navMesh;
        speed = _speed;
        pathRefreshRate = _pathRefreshRate;
        positionLocked = _positionLocked;

        return this;
    }


    bool NavMeshAgent::UpdatePathToDestination()
    {
        currentPath = navMesh->CalculatePathWithSmoothing(owner->transform.pos, destination);
        return currentPath.size() != 0;
    }


    ComponentID NavMeshAgent::GetID() const
    {
        return ComponentID::NAVMESH_AGENT;
    }
}
