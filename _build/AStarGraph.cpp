#include "AStarGraph.h"

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


	std::vector<AStarNode*> AStarGraph::GetPath(AStarNode* start, AStarNode* end)
	{
		std::vector<AStarNode*> frontier(nodes.size());
		std::vector<AStarNode*> closed(nodes.size());
		std::vector<AStarNode*> open(nodes.size());

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