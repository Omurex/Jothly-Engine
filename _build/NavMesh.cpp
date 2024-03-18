#include "NavMesh.h"
#include <set>
#include <map>
#include <unordered_map>
#include <functional>
#include <unordered_set>
#include <iostream>
#include "Math.h"


namespace jothly
{
	struct Edge
	{
		union
		{
			struct
			{
				DelaunayPoint p0;
				DelaunayPoint p1;
			};

			DelaunayPoint p[2];
		};


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
			else if(p0.pos.x == p1.pos.x)
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


		Vector2 CalculateMidPoint() { return (p0.pos + p1.pos) / 2.0f; }

		bool HasPoint(DelaunayPoint& point)
		{
			return p0 == point || p1 == point;
		}

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


	struct DelaunayPointCompare
	{
		std::size_t operator()(const DelaunayPoint& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			return ((hash<float>()(k.pos.x)
				^ (hash<float>()(k.pos.y) << 1)) >> 1);
		};
	};


	NavMesh* NavMesh::Init(float _pointRadius, Color _pointColor, bool _drawPoints, float _lineThickness, 
		Color _lineColor, bool _drawTriangles, float _obstaclePointRadius, Color _obstaclePointColor, 
		bool _drawObstaclePoints, bool _drawObstacles, bool _drawAStar)
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
		drawAStar = _drawAStar;

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


	int NavMesh::FindTriangleIndexContainingPoint(Vector2 point)
	{
		// Optimize this later with binary search (use edges that are sorted? make the maps we generate during astar member vars)
		for(int i = 0; i < triangles.size(); i++)
		{
			if(triangles[i].ContainsPointInTriangle(point))
			{
				return i;
			}
		}

		return -1;
	}


	bool NavMesh::DoesLineIntersectWithAnyObstacles(Vector2 p0, Vector2 p1)
	{
		for (int i = 0; i < obstacles.size(); i++)
		{
			if (obstacles[i]->DoesLineSegmentIntersectObstacle(p0, p1))
			{
				return true;
			}
		}

		return false;
	}


	void NavMesh::SmoothPath(std::vector<Vector2>& path)
	{
		if (IsKeyDown(KEY_BACKSPACE))
		{
			std::cout << "stop" << std::endl;
		}

		std::vector<Vector2> smoothedPath;
		smoothedPath.reserve(path.size());

		int numSkips;

		for(int i = 0; i < path.size(); i += numSkips)
		{
			numSkips = 1;

			// Make sure we're not out of bounds of path array
			while(i + numSkips + 1 < path.size())
			{
				if (DoesLineIntersectWithAnyObstacles(path[i], path[i + numSkips + 1]))
				{
					break;
				}

				numSkips += 1;
			}

			smoothedPath.push_back(path[i]);
		}

		if (path.size() != smoothedPath.size())
		{
			SmoothPath(smoothedPath);
		}

		path = smoothedPath;
	}


	ComponentID NavMesh::GetID() const
	{
		return ComponentID::NAVMESH;
	}


	void NavMesh::AddObstacle(NavMeshObstacle* obstacle)
	{
		obstacles.push_back(obstacle);
	}


	void NavMesh::AddObstacles(std::vector<NavMeshObstacle>& newObstacles)
	{
		obstacles.reserve(obstacles.size() + newObstacles.size());

		for (int i = 0; i < newObstacles.size(); i++)
		{
			obstacles.push_back(&newObstacles[i]);
		}
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

		DelaunayTriangle superTriangle = CalculateSuperTriangle();
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


	bool NavMesh::CalculatePointBounds(Vector2& out_lb, Vector2& out_ub)
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


	DelaunayTriangle NavMesh::CalculateSuperTriangle()
	{
		const float BUFFER_AMOUNT = 100;
		const float MULT_AMOUNT = 1;

		Vector2 lb;
		Vector2 ub;

		bool boundsValid = CalculatePointBounds(lb, ub);

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
		graph.ReserveGraphSize(triangles.size());

		triangleToAStarPoints.resize(triangles.size());

		// Since we know each triangle will have 6 astar points (3 vertices, 3 midpoints), reserve arrays now
		// so that they don't dynamically resize while running
		for(int i = 0; i < triangleToAStarPoints.size(); ++i)
		{
			triangleToAStarPoints[i].reserve(6);
		}

		/*std::vector<Edge> edges;
		edges.reserve(triangles.size() * 3);*/

		// Key: Appropriately flipped edge, Value: Triangle indexes in triangles vector
		// Holds what two triangles share an edge
		std::unordered_map<Edge, std::vector<int>, EdgeCompare> edgeToTriangles;

		std::vector<std::vector<Edge>> trianglesToEdges(triangles.size()); // Index = triangle index in triangles array, values = edges of triangle

		std::unordered_map<DelaunayPoint, std::vector<Edge>, DelaunayPointCompare> pointToEdges; // Index = index in point array, value = edges that have an endpoint at that point

		std::unordered_map<DelaunayPoint, AStarNode*, DelaunayPointCompare> pointToNode;

		std::unordered_map<Edge, AStarNode*, EdgeCompare> edgeToMidpointAStarNode;

		//std::vector<int> nodeIndexToTriangleIndex;

		for (int i = 0; i < triangles.size(); i++)
		{
			DelaunayTriangle tri = triangles[i];

			Edge triEdges[] = { 
				Edge(tri.points[0], tri.points[1]),
				Edge(tri.points[1], tri.points[2]),
				Edge(tri.points[2], tri.points[0])
			};


			for(int j = 0; j < 3; j++)
			{
				Edge e = triEdges[j];
				e.FlipBasedOnCoordinates();

				if (edgeToTriangles.find(e) == edgeToTriangles.end()) // Edge not in map, put it in
				{
					edgeToTriangles.insert({e, {i, -1}}); // Add edge with first element in value being this triangle index
				}
				else
				{
					edgeToTriangles[e][1] = i; // Make second element in value be this triangle index
				}

				for(int k = 0; k < 2; ++k) // For each endpoint of edge, load pointToEdges map with appropriate data
				{
					DelaunayPoint edgePoint = e.p[k];

					// Fill out point to edges map
					if (pointToEdges.find(edgePoint) == pointToEdges.end())
					{
						pointToEdges.insert({ edgePoint, std::vector<Edge> { e }});
					}
					// Make sure edge isn't already accounted for
					else if (std::find(pointToEdges[edgePoint].begin(), pointToEdges[edgePoint].end(), e) == pointToEdges[edgePoint].end())
					{
						pointToEdges[edgePoint].push_back(e);
					}
				}
			}

			trianglesToEdges[i] = std::vector<Edge>(triEdges, triEdges + 3);
		}

		
		// Add midpoint astar nodes to graph
		for(auto it = edgeToTriangles.begin(); it != edgeToTriangles.end(); ++it)
		{
			Edge edge = it->first;
			edgeToMidpointAStarNode.insert({ edge, graph.CreateNode(edge.CalculateMidPoint()) });
		}


		// Set up astar points
		for(auto it = pointToEdges.begin(); it != pointToEdges.end(); ++it)
		{
			pointToNode.insert( { it->first, graph.CreateNode(it->first.pos) } );
		}

		for(auto it = pointToNode.begin(); it != pointToNode.end(); ++it) // Loop through each point, and its associated AStar
		{
			AStarNode* node = pointToNode[it->first];
			std::vector<Edge>& connectedEdges = pointToEdges[it->first];

			for(int i = 0; i < connectedEdges.size(); ++i)
			{
				node->Form2WayConnection(edgeToMidpointAStarNode[connectedEdges[i]]);

				// Use below commented code if we're connecting vertices in triangle to each other, not using midpoints
				//if(it->first == connectedEdges[i].p0) // p0 is this, so connect p1
				//{
				//	node->Form1WayConnection(pointToNode[connectedEdges[i].p1]);
				//}
				//else // p1 is this, so connect p0
				//{
				//	node->Form1WayConnection(pointToNode[connectedEdges[i].p0]);
				//}
			}
		}


		// Connect edge midpoints in triangle
		for(auto it = edgeToTriangles.begin(); it != edgeToTriangles.end(); ++it) // Loop through each edge
		{
			Edge edge = it->first;
			std::vector<int>& triangleIndexes = it->second;
			AStarNode* edgeMidPoint = edgeToMidpointAStarNode[edge];

			for (int i = 0; i < 2; ++i) // Loop through triangles edge is connected to
			{
				int triIndex = triangleIndexes[i];

				if(triIndex < 0) continue; // No second triangle has this edge

				triangleToAStarPoints[triIndex].push_back(edgeMidPoint); // Log midpoints in triangle to astar dict

				DelaunayTriangle& tri = triangles[triIndex];

				std::vector<Edge>& triEdges = trianglesToEdges[triIndex];

				for(int j = 0; j < triEdges.size(); ++j) // Loop through each edge of the triangle
				{
					Edge triEdge = triEdges[j];

					if(edge == triEdge) continue; // Don't connect edge midpoint to itself

					AStarNode* triEdgeMidPoint = edgeToMidpointAStarNode[triEdge];

					edgeMidPoint->Form2WayConnection(triEdgeMidPoint);

					// For each edge, connect midpoint to opposing vertex
					for(int k = 0; k < 3; ++k)
					{
						DelaunayPoint triVertex = tri.points[k];

						if(triEdge.HasPoint(triVertex)) continue; // Point is on this edge, not opposite we're looking for
					
						triEdgeMidPoint->Form2WayConnection(pointToNode[triVertex]);

						break;
					}
				}
			}
		}

		// Add vertex astar points to mapping
		for(int i = 0; i < triangles.size(); ++i)
		{
			for(int j = 0; j < 3; ++j)
			{
				triangleToAStarPoints[i].push_back(pointToNode[triangles[i].points[j]]);
			}
		}

		return graph;
	}


	bool NavMesh::FindTriangleContainingPoint(Vector2 point, DelaunayTriangle& out_triangle)
	{
		int index = FindTriangleIndexContainingPoint(point);

		if(index < 0) return false;

		out_triangle = triangles[index];

		return true;
	}


	std::vector<Vector2> NavMesh::CalculatePathWithoutSmoothing(Vector2 start, Vector2 end, bool removeFirst, bool removeLast)
	{
		int startTriangleIndex = FindTriangleIndexContainingPoint(start);
		int endTriangleIndex = FindTriangleIndexContainingPoint(end);

		if (startTriangleIndex < 0) { std::cout << "No triangle containing start point\n"; return std::vector<Vector2>(); }
		if (endTriangleIndex < 0) { std::cout << "No triangle containing end point\n"; return std::vector<Vector2>(); }

		DelaunayPoint* startPoints = triangles[startTriangleIndex].points;
		DelaunayPoint* endPoints = triangles[endTriangleIndex].points;

		/*std::cout << "Points containing start: " + startPoints[0].pos.ToString() + " , " + startPoints[1].pos.ToString() + " , " +
			startPoints[2].pos.ToString() + "\n";

		std::cout << "Points containing end: " + endPoints[0].pos.ToString() + " , " + endPoints[1].pos.ToString() + " , " +
			endPoints[2].pos.ToString() + "\n";*/

		std::vector<AStarNode*> startTriangleAStar = triangleToAStarPoints[startTriangleIndex];
		std::vector<AStarNode*> endTriangleAStar = triangleToAStarPoints[endTriangleIndex];

		AStarNode* startNode = graph.CreateNode(start);
		AStarNode* endNode = graph.CreateNode(end);

		// Connect temporary start and end node to astar system
		for (int i = 0; i < startTriangleAStar.size(); ++i)
		{
			startNode->Form2WayConnection(startTriangleAStar[i]);
		}

		for (int i = 0; i < endTriangleAStar.size(); ++i)
		{
			endNode->Form2WayConnection(endTriangleAStar[i]);
		}

		std::vector<AStarNode*> aStarPath = graph.CalculatePath(startNode, endNode, removeFirst, removeLast);
		std::vector<Vector2> path(aStarPath.size());

		// Convert astar path to positions
		for (int i = 0; i < aStarPath.size(); ++i)
		{
			path[i] = aStarPath[i]->pos;
		}

		// Remove temporary start and end node from astar system
		for (int i = 0; i < startTriangleAStar.size(); ++i)
		{
			startNode->Remove2WayConnection(startTriangleAStar[i]);
		}

		for (int i = 0; i < endTriangleAStar.size(); ++i)
		{
			endNode->Remove2WayConnection(endTriangleAStar[i]);
		}

		return path;
	}


	std::vector<Vector2> NavMesh::CalculatePathWithSmoothing(Vector2 start, Vector2 end, bool removeFirst, bool removeLast)
	{
		std::vector<Vector2> path = CalculatePathWithoutSmoothing(start, end, removeFirst, removeLast);

		SmoothPath(path);

		return path;
	}
}