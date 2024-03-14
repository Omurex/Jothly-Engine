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


	struct CompareNodePathCosts
	{
		bool operator() (AStarNode* const node0, AStarNode* const node1)
		{
			return node1->GetPathCost() < node0->GetPathCost();
		}
	};


	// https://theory.stanford.edu/~amitp/GameProgramming/MapRepresentations.html
	std::vector<AStarNode*> AStarGraph::GetPath(AStarNode* start, AStarNode* end)
	{
		std::unordered_set<AStarNode*> closed; // Shortest path already calculated for all these nodes

		// https://stackoverflow.com/questions/16111337/declaring-a-priority-queue-in-c-with-a-custom-comparator
		// https://en.cppreference.com/w/cpp/language/decltype
		std::priority_queue<AStarNode*, std::vector<AStarNode*>, CompareNodePathCosts> open;

		closed.reserve(nodes.size());

		open.push(start);

		while (!open.empty())
		{
			// Get lowest path cost node
			AStarNode* node = open.top();
			open.pop();

			if(closed.find(node) != closed.end()) continue; // Node already visited

			for(int i = 0; i < node->connections.size(); i++)
			{
			}
		}

		return std::vector<AStarNode*>();
	}


	void AStarGraph::Clear()
	{
		for (int i = nodes.size() - 1; i >= 0; --i)
		{
			delete nodes[i];
		}
	}


	void AStarGraph::Draw()
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			nodes[i]->Draw(nodeColor, nodeRadius, nodeConnectionLineColor, nodeConnectionLineThickness);
		}
	}
}