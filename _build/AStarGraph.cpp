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


	// https://theory.stanford.edu/~amitp/GameProgramming/MapRepresentations.html
	std::vector<AStarNode*> AStarGraph::GetPath(AStarNode* start, AStarNode* end)
	{
		std::unordered_set<AStarNode*> closed;
		std::priority_queue<AStarNode*> open;

		closed.reserve(nodes.size());

		open.push(start);

		while (!open.empty())
		{
			
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