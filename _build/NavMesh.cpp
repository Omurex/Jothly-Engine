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
}