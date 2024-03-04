#include "NavMesh.h"
#include <set>
#include <map>
#include <unordered_map>>
#include <functional>


namespace jothly
{
	struct Edge
	{
		DelaunayPoint p0;
		DelaunayPoint p1;


		Edge(DelaunayPoint _p0, DelaunayPoint _p1) { p0 = _p0; p1 = _p1; }
		Edge(const Edge& other) { p0 = other.p0; p1 = other.p1; }


		bool operator==(const Edge& other) const
		{
			return (p0 == other.p0 && p1 == other.p1)
				|| (p1 == other.p0 && p0 == other.p1);
		}


		Edge GetFlippedBasedOnCoordinates() const
		{
			Edge newEdge = *this;
			newEdge.FlipBasedOnCoordinates();
			return newEdge;
		}


		void FlipBasedOnCoordinates()
		{
			if(p0.pos.x > p1.pos.x)
			{
				Flip();
			}
			else if(p0.pos == p1.pos)
			{
				if(p0.pos.y > p1.pos.y)
				{
					Flip();
				}
			}
		}


		void Flip()
		{
			DelaunayPoint temp = p0;
			p0 = p1;
			p1 = temp;
		}


		/*bool operator<(const Edge& other) const
		{
			Edge edge1 = *this;
			Edge edge2 = other;

			edge1.FlipBasedOnCoordinates();
			edge2.FlipBasedOnCoordinates();

			return edge1.p0.pos.x < edge2.p0.pos.x;
		}*/


		// https://stackoverflow.com/questions/17016175/c-unordered-map-using-a-custom-class-type-as-the-key
		//std::size_t operator()(const Edge& k) const
		//{
		//	using std::size_t;
		//	using std::hash;
		//	using std::string;

		//	// Compute individual hash values for first,
		//	// second and third and combine them using XOR
		//	// and bit shifting:

		//	Edge newEdge = GetFlippedBasedOnCoordinates();

		//	return ((hash<float>()(newEdge.p0.pos.x)
		//		^ (hash<float>()(newEdge.p0.pos.y) << 1)) >> 1)
		//		^ (hash<float>()(newEdge.p1.pos.x) << 1)
		//		^ (hash<float>()(newEdge.p1.pos.y) << 1);
		//}


	};


	// https://stackoverflow.com/questions/1102392/how-can-i-use-stdmaps-with-user-defined-types-as-key
	struct EdgeCompare
	{
		std::size_t operator()(const Edge& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

				Edge newEdge = k.GetFlippedBasedOnCoordinates();

			return ((hash<float>()(newEdge.p0.pos.x)
				^ (hash<float>()(newEdge.p0.pos.y) << 1)) >> 1)
				^ (hash<float>()(newEdge.p1.pos.x) << 1)
				^ (hash<float>()(newEdge.p1.pos.y) << 1);
		}
	};


	NavMesh* NavMesh::Init(float _pointRadius, Color _pointColor, bool _drawPoints, float _lineThickness, 
		Color _lineColor, bool _drawTriangles, float _obstaclePointRadius, Color _obstaclePointColor, 
		bool _drawObstaclePoints, bool _drawObstacles)
	{
		pointRadius = _pointRadius;
		pointColor = _pointColor;
		lineThickness = _lineThickness;
		lineColor = _lineColor;
		obstaclePointRadius = _obstaclePointRadius;
		obstaclePointColor = _obstaclePointColor;

		drawPoints = _drawPoints;
		drawTriangles = _drawTriangles;
		drawObstaclePoints = _drawObstaclePoints;
		drawObstacles = _drawObstacles;

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

		if (drawObstaclePoints)
		{
			for (int i = 0; i < obstaclePoints.size(); i++)
			{
				obstaclePoints[i].Draw(obstaclePointRadius, obstaclePointColor);
			}
		}

		if (drawObstacles)
		{
			for (int i = 0; i < obstacles.size(); i++)
			{
				obstacles[i]->Draw();
			}
		}

		if (drawAStar)
		{
			graph.Draw();
		}
	}


	ComponentID NavMesh::GetID() const
	{
		return ComponentID::NAVMESH;
	}


	void NavMesh::AddObstacle(NavMeshObstacle* obstacle)
	{
		obstacles.push_back(obstacle);
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


	void NavMesh::LoadObstaclePoints(std::vector<Vector2> _obstaclePoints)
	{
		obstaclePoints.clear();

		obstaclePoints.resize(_obstaclePoints.size());

		for (int i = 0; i < obstaclePoints.size(); i++)
		{
			obstaclePoints[i] = DelaunayPoint(_obstaclePoints[i]);
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

		int loggedPointsSize = points.size();
		int loggedObstaclePointsSize = obstaclePoints.size();

		for (int i = 0; i < obstacles.size(); i++)
		{
			std::vector<DelaunayPoint> obstacleNavMeshPoints = obstacles[i]->GetNavMeshPoints();
			std::vector<DelaunayPoint> obstacleObstaclePoints = obstacles[i]->GetObstaclePoints();

			points.insert(points.end(), obstacleNavMeshPoints.begin(), obstacleNavMeshPoints.end());
			obstaclePoints.insert(obstaclePoints.end(), obstacleObstaclePoints.begin(), obstacleObstaclePoints.end());
		}

		for (int i = points.size() - 1; i >= 0; --i)
		{
			for (int j = 0; j < obstacles.size(); ++j)
			{
				if (obstacles[j]->IsPointInObstacle(points[i].pos))
				{
					points.erase(points.begin() + i);
				}
			}
		}

		points.insert(points.end(), obstaclePoints.begin(), obstaclePoints.end());

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
				triangles.erase(triangles.begin() + badTriangleIndexes[j]);
			}

			EraseDuplicateEdges(edges);

			for (int j = 0; j < edges.size(); j++)
			{
				triangles.push_back(DelaunayTriangle(edges[j].p0, edges[j].p1, pointToAdd));
			}
		}

		// Cleanup super triangle and obstacle triangles
		for (int i = triangles.size() - 1; i >= 0; --i)
		{
			DelaunayTriangle tri = triangles[i];

			if (tri.HasPoint(superTriangle.points[0]) || tri.HasPoint(superTriangle.points[1])
				|| tri.HasPoint(superTriangle.points[2]))
			{
				triangles.erase(triangles.begin() + i);
				continue;
			}
			
			for (int j = 0; j < obstaclePoints.size(); ++j)
			{
				if (tri.HasPoint(obstaclePoints[j]))
				{
					triangles.erase(triangles.begin() + i);
					break;
				}
			}
		}

		points.resize(loggedPointsSize); // Get rid of obstacle points from points list
		obstaclePoints.resize(loggedObstaclePointsSize);

		GenerateAStarGraph();

		return true;
    }


	void NavMesh::AddPoints(std::vector<Vector2> _points)
	{
		points.reserve(points.size() + _points.size());

		for (int i = 0; i < _points.size(); ++i)
		{
			points.push_back(_points[i]);
		}
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
		const float MULT_AMOUNT = 1;

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


	AStarGraph& NavMesh::GenerateAStarGraph()
	{
		graph.Clear();

		std::vector<Edge> edges;
		edges.reserve(triangles.size() * 3);

		for (int i = 0; i < triangles.size(); i++)
		{
			DelaunayTriangle tri = triangles[i];

			edges.push_back({ tri.points[0], tri.points[1] });
			edges.push_back({ tri.points[1], tri.points[2] });
			edges.push_back({ tri.points[2], tri.points[0] });

			graph.CreateNode(tri.GetCentroid());
		}

		EraseDuplicateEdges(edges);

		//std::unordered_map<Edge, std::vector<int>> edgesToTriangles;
		std::unordered_map<Edge, std::vector<int>, EdgeCompare> edgesToTriangles;

		for(int i = 0; i < edges.size(); i++)
		{
			Edge edge = edges[i];

			if(edgesToTriangles.find(edge) == edgesToTriangles.end()) // Not in map
			{
				edgesToTriangles.insert({edge, {-1, -1}});
			}
		}

		return graph;
	}
}