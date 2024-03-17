#include "AStarGraph.h"
#include <queue>
#include <unordered_set>


namespace jothly
{
	AStarGraph::~AStarGraph()
	{
		Clear();
	}


	AStarNode* AStarGraph::CreateNode(Vector2 pos)
	{
		AStarNode* newNode = new AStarNode(pos);
		nodes.push_back(newNode);
		return newNode;
	}


	struct CompareNodeScores
	{
		bool operator() (AStarNode* const node0, AStarNode* const node1)
		{
			return node1->GetScore() < node0->GetScore();
		}
	};


	std::vector<AStarNode*> ConstructPath(AStarNode* end)
	{
		std::vector<AStarNode*> path;
		if(end->GetPathParent() == nullptr) return path; // If no solution found, return empty vector

		AStarNode* node = end;

		while(node != nullptr)
		{
			path.push_back(node);
			node = node->GetPathParent();
		}

		std::reverse(path.begin(), path.end());

		return path;
	}


	// https://theory.stanford.edu/~amitp/GameProgramming/MapRepresentations.html
	std::vector<AStarNode*> AStarGraph::CalculatePath(AStarNode* start, AStarNode* end)
	{
		if(start == end) // If we try navigating to same spot, path will only have this spot's node
		{
			lastPathComputedDestination = end;
			return std::vector { start };
		}

		std::unordered_set<AStarNode*> closed; // Shortest path already calculated for all these nodes

		// https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
		// https://en.cppreference.com/w/cpp/language/decltype
		std::priority_queue<AStarNode*, std::vector<AStarNode*>, CompareNodeScores> open;

		for(int i = 0; i < nodes.size(); i++)
		{
			nodes[i]->ResetPathFindingVariables();
		}

		start->SetPathCost(0);

		closed.reserve(nodes.size());

		open.push(start);

		while (!open.empty())
		{
			// Get lowest path score node
			AStarNode* node = open.top();
			open.pop();

			if(closed.find(node) != closed.end()) continue; // Node already visited
			if(node == end)
			{
				break;
			}

			for(int i = 0; i < node->connections.size(); ++i)
			{
				AStarNode* connection = node->connections[i];

				if(connection->UpdatePathDataWithLowerScore(node))
				{
					connection->UpdateHeuristicFromEnd(end); // Make sure heuristic is properly updated before pushing
					
					open.push(connection);
				}
			}

			closed.insert(node);
		}

		std::vector<AStarNode*> path = ConstructPath(end);

		lastPathComputedDestination = end;

		return path;
	}


	void AStarGraph::Clear()
	{
		for (int i = nodes.size() - 1; i >= 0; --i)
		{
			delete nodes[i];
		}
	}


	void AStarGraph::Draw(bool drawNodes, bool drawConnections, bool drawLastComputedPath)
	{
		float nodeRadiusToDraw = 0;
		float nodeConnectionLineThicknessToDraw = 0;

		if(drawNodes) nodeRadiusToDraw = nodeRadius;
		if(drawConnections) nodeConnectionLineThicknessToDraw = nodeConnectionLineThickness;

		for (int i = 0; i < nodes.size(); ++i)
		{
			nodes[i]->Draw(nodeColor, nodeRadiusToDraw, nodeConnectionLineColor, nodeConnectionLineThicknessToDraw);
		}

		if(drawLastComputedPath && lastPathComputedDestination != nullptr)
		{
			AStarNode* fromNode = lastPathComputedDestination;
			AStarNode* toNode = lastPathComputedDestination->GetPathParent();
			
			while(toNode != nullptr)
			{
				fromNode->DrawConnection(toNode, pathLineColor, pathLineThickness);
				fromNode = toNode;
				toNode = toNode->GetPathParent();
			}
		}
	}
}