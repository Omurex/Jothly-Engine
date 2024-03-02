#include "NavMesh.h"


namespace jothly
{
	NavMesh* NavMesh::Init(float _pointRadius, Color _pointColor, bool _drawPoints, float _lineThickness, Color _lineColor, bool _drawTriangles)
	{
		pointRadius = _pointRadius;
		pointColor = _pointColor;
		lineThickness = _lineThickness;
		lineColor = _lineColor;

		drawPoints = _drawPoints;
		drawTriangles = _drawTriangles;

		return this;
	}


	void NavMesh::Draw()
	{
		if (drawTriangles)
		{
			float pRad = 0;

			if(drawPoints) pRad = pointRadius;

			for (int i = 0; i < triangles.size(); i++)
			{
				triangles[i].Draw(lineThickness, lineColor, pRad, pointColor);
			}
		}
		else if(drawPoints)
		{
			for(int i = 0; i < points.size(); i++)
			{
				points[i].Draw(pointRadius, pointColor);
			}
		}
	}


	ComponentID NavMesh::GetID() const
	{
		return ComponentID::NAVMESH;
	}


	void NavMesh::LoadPoints(std::vector<Vector2> _points)
	{
		points.clear();

		points.resize(_points.size());

		for(int i = 0; i < points.size(); i++)
		{
			points[i] = DelaunayPoint(_points[i]);
		}
	}


    bool NavMesh::GenerateDelaunayTriangles()
    {
		if (points.size() < 3) return false;

		triangles.clear();
		triangles.reserve((points.size() / 2.0f) + 8);

		//triangles[0] = 

		triangles.push_back(DelaunayTriangle(points[0], points[1], points[2]));

		// Loop through each point and add it to delaunay
		for (int i = 3; i < points.size(); i++)
		{
			// Note: At some point cache circumcenter and circumradius so we don't have to recalculate
			DelaunayPoint pointToAdd = points[i];

			for (int i = 0; i < triangles.size(); i++)
			{
				Vector2 center = triangles[i].GetCircumcenter();
				float radius = triangles[i].GetCircumradius();

				if ((pointToAdd.pos - center).GetMagnitudeSquared() <= radius * radius) // Check if point in circle
				{

				}
			}
		}

		return true;
    }


	bool NavMesh::GetPointBounds(Vector2& out_lb, Vector2& out_ub)
	{
		if (points.size() <= 0) return false;

		constexpr float MAX_FLOAT = std::numeric_limits<float>::max();
		out_lb = Vector2(MAX_FLOAT, MAX_FLOAT);
		out_ub = Vector2(-MAX_FLOAT, -MAX_FLOAT);

		for (int i = 0; i < points.size(); i++)
		{
			Vector2 point = points[i].pos;

			if (point.x < out_lb.x) out_lb.x = point.x;
			if (point.y < out_lb.y) out_lb.y = point.y;

			if (point.x > out_ub.x) out_ub.x = point.x;
			if (point.y > out_ub.y) out_ub.y = point.y;
		}

		return true;
	}


	DelaunayTriangle NavMesh::GetSuperTriangle()
	{
		const float BUFFER_AMOUNT = 5;

		Vector2 lb;
		Vector2 ub;

		bool boundsValid = GetPointBounds(lb, ub);

		if (!boundsValid) return DelaunayTriangle();

		lb.x -= BUFFER_AMOUNT;
		lb.y -= BUFFER_AMOUNT;
		ub.x += BUFFER_AMOUNT;
		ub.y += BUFFER_AMOUNT;

		float height = ub.y - lb.y;
		float halfWidth = (ub.x - lb.x) / 2.0f;

		return DelaunayTriangle(
			Vector2(((lb.x + ub.x) / 2.0f), ub.y + height), // Top point
			Vector2(ub.x + halfWidth, lb.y), // Right bottom point
			Vector2(lb.x - halfWidth, lb.y) // Left bottom point
		);
	}


	// https://stackoverflow.com/questions/686353/random-float-number-generation
	void NavMesh::GenerateRandomPoints(int numPoints, Vector2 lowerbound, Vector2 upperbound)
	{
		std::vector<Vector2> randomPoints(numPoints);

		for(int i = 0; i < numPoints; i++)
		{
			randomPoints[i] = Vector2(
				lowerbound.x + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (upperbound.x - lowerbound.x))),
				lowerbound.y + static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / (upperbound.y - lowerbound.y)))
			);
		}

		LoadPoints(randomPoints);
	}
}