#include "NavMeshAgent.h"

namespace jothly
{
    void NavMeshAgent::Update(float dt)
    {
        TravelPath(dt);
    }


    NavMeshAgent* NavMeshAgent::Init(NavMesh* _navMesh, float _speed, float _pathRefreshRate, bool _positionLocked)
    {
        navMesh = _navMesh;
        speed = _speed;
        pathRefreshRate = _pathRefreshRate;
        navigating = _positionLocked;

        return this;
    }


    bool NavMeshAgent::UpdatePathToDestination()
    {
        currentPath = navMesh->CalculatePathWithSmoothing(owner->transform.pos, destination, true, false);

        if (currentPath.size() > 0) // Path successfully generated
        {
            currentPathIndex = 0;
            return true;
        }
        else
        {
            currentPathIndex = -1;
            return false;
        }
    }


    void NavMeshAgent::MoveTowardsPoint(Vector2 point, float dt)
    {
        Vector2 dir = (point - owner->transform.pos).GetNormalized();
        owner->transform.pos += dir * speed * dt;
    }


    void NavMeshAgent::TravelPath(float dt)
    {

    }


    ComponentID NavMeshAgent::GetID() const
    {
        return ComponentID::NAVMESH_AGENT;
    }
}
