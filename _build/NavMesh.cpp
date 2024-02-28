#include "NavMesh.h"

namespace jothly
{
	NavMesh* NavMesh::Init(float _pointRadius, Color _pointColor, float _lineThickness, Color _lineColor)
	{
		pointRadius = _pointRadius;
		pointColor = _pointColor;
		lineThickness = _lineThickness;
		lineColor = _lineColor;

		return this;
	}


	void NavMesh::Draw()
	{
		for (int i = 0; i < triangles.size(); i++)
		{
			triangles[i].Draw(lineThickness, lineColor, pointRadius, pointColor);
		}
	}


	ComponentID NavMesh::GetID() const
	{
		return ComponentID::NAVMESH;
	}
}