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
        return false;
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