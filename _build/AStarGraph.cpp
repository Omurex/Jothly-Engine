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