#include "NavMeshAgent.h"

namespace jothly
{
    void NavMeshAgent::Update(float dt)
    {
        TravelPath(dt);
    }


    NavMeshAgent* NavMeshAgent::Init(NavMesh* _navMesh, float _speed, float _pathRefreshRate, float _pathPointCheckRadius, bool _positionLocked)
    {
        navMesh = _navMesh;
        speed = _speed;
        pathRefreshRate = _pathRefreshRate;
        navigating = _positionLocked;
        pathPointCheckRadius = _pathPointCheckRadius;

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
        if (currentPathIndex < 0) return;

        Vector2 nextPoint = currentPath[currentPathIndex];

        MoveTowardsPoint(nextPoint, dt);

        // Reached point
        if ((owner->transform.pos - nextPoint).GetMagnitudeSquared() < pathPointCheckRadius * pathPointCheckRadius)
        {
            ++currentPathIndex;

            if (currentPathIndex >= currentPath.size()) currentPathIndex = -1; // Reached end of path!
        }
    }


    ComponentID NavMeshAgent::GetID() const
    {
        return ComponentID::NAVMESH_AGENT;
    }
}
