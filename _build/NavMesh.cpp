#include "NavMesh.h"
#include <set>


namespace jothly
{
	struct Edge
	{
		DelaunayPoint p0;
		DelaunayPoint p1;

		bool operator==(const Edge& other)
		{
			return (p0 == other.p0 && p1 == other.p1)
				|| (p1 == other.p0 && p0 == other.p1);
		}
	};


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


	// Remove duplicate edges from edges array
	void EraseDuplicateEdges(std::vector<Edge>& edges)
	{
		std::set<int> edgeIndexesToRemove;

		for (int i = 0; i < edges.size(); i++)
		{
			for (int j = i + 1; j < edges.size(); j++)
			{
				if (edges[i] == edges[j])
				{
					edgeIndexesToRemove.insert(i);
					edgeIndexesToRemove.insert(j);
				}
			}
		}

		// Remove all edges marked as duplicate
		for (auto it = edgeIndexesToRemove.rbegin(); it != edgeIndexesToRemove.rend(); ++it)
		{
			edges.erase(edges.begin() + *it);
		}
	}


    bool NavMesh::GenerateDelaunayTriangles()
    {
		if (points.size() < 3) return false;

		int reserveSize = (points.size() / 2.0f) + 8;

		triangles.clear();
		triangles.reserve(reserveSize);

		DelaunayTriangle superTriangle = GetSuperTriangle();
		triangles.push_back(superTriangle);

		std::vector<int> badTriangleIndexes;
		badTriangleIndexes.reserve(reserveSize);

		std::vector<Edge> edges;
		edges.reserve(reserveSize * 3);

		// Loop through each point and add it to delaunay
		for (int i = 0; i < points.size(); i++)
		{
			badTriangleIndexes.clear();
			edges.clear();

			// Note: At some point cache circumcenter and circumradius so we don't have to recalculate
			DelaunayPoint pointToAdd = points[i];

			// Loop through triangles looking to see if their circumcircles contain our point we're adding
			for (int j = 0; j < triangles.size(); j++)
			{
				DelaunayTriangle& tri = triangles[j];

				Vector2 center = triangles[j].GetCircumcenter();
				float radius = triangles[j].GetCircumradius();

				float dist = (pointToAdd.pos - center).GetMagnitude();

				if (dist < radius) // Check if point in circle
				{
					badTriangleIndexes.push_back(j);
					edges.push_back({ tri.points[0], tri.points[1] });
					edges.push_back({ tri.points[1], tri.points[2] });
					edges.push_back({ tri.points[2], tri.points[0] });
				}
			}

			// Get rid of any triangles that had invalid circumcircles
			for (int j = badTriangleIndexes.size() - 1; j >= 0; --j)
			{
				//if(j != 0) // Don't delete super triangle
				triangles.erase(triangles.begin() + j);
			}

			EraseDuplicateEdges(edges);

			for (int j = 0; j < edges.size(); j++)
			{
				triangles.push_back(DelaunayTriangle(edges[j].p0, edges[j].p1, pointToAdd));
			}
		}

		for (int i = triangles.size() - 1; i >= 0; --i)
		{
			DelaunayTriangle tri = triangles[i];

			if (tri.HasPoint(superTriangle.points[0]) || tri.HasPoint(superTriangle.points[1])
				|| tri.HasPoint(superTriangle.points[2]))
			{
				triangles.erase(triangles.begin() + i);
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
		const float BUFFER_AMOUNT = 100;
		const float MULT_AMOUNT = 100;

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
			Vector2(((lb.x + ub.x) / 2.0f), ub.y + (height * MULT_AMOUNT)), // Top point
			Vector2(ub.x + (halfWidth * MULT_AMOUNT), lb.y - (BUFFER_AMOUNT * MULT_AMOUNT)), // Right bottom point
			Vector2(lb.x - (halfWidth * MULT_AMOUNT), lb.y - (BUFFER_AMOUNT * MULT_AMOUNT)) // Left bottom point
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