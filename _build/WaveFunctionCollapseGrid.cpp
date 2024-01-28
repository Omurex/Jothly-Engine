#include "WaveFunctionCollapseGrid.h"


namespace jothly
{
	void WaveFunctionCollapseGrid::Draw()
	{
		Vector2 tileSize = Vector2(gridSize.x / numCellsX, gridSize.y / numCellsY);

		for (int x = 0; x < numCellsX; x++)
		{
			float xPos = ((float)x / numCellsX) * gridSize.x;

			for (int y = 0; y < numCellsY; y++)
			{
				Vector2 topLeftPos = Vector2(xPos, ((float)y / numCellsY) * gridSize.y);
				topLeftPos += owner->transform.pos;
				topLeftPos += offset;
				GetTile(x, y)->DrawTile(topLeftPos, tileSize);
			}
		}
	}


	WaveFunctionCollapseGrid* WaveFunctionCollapseGrid::Init(std::vector<WaveFunctionCollapseTile>& _templateTiles, 
		Vector2 _offset, Vector2 _gridSize)
	{
		SetTemplateTiles(_templateTiles);
		SetOffset(_offset);
		SetGridSize(_gridSize);

		return this;
	}


	void WaveFunctionCollapseGrid::GenerateInitialGrid(int _numCellsX, int _numCellsY)
	{
		ClearGrid();

		numCellsX = _numCellsX;
		numCellsY = _numCellsY;

		tiles = new WaveFunctionCollapseTile[numCellsX * numCellsY];
		for (int x = 0; x < numCellsX; x++)
		{
			for (int y = 0; y < numCellsY; y++)
			{
				// Loop through grid for any initialization steps
				GetTile(x, y)->LoadPossibilities(templateTiles);
			}
		}
	}


	void WaveFunctionCollapseGrid::Run()
	{
		// Find least entropy
		// Pick random fit given neighbors

		int numCells = numCellsX * numCellsY;
		std::vector<int> notCollapsedIndexes = std::vector<int>(numCells);

		int numCollapsed = 0;

		for (int i = 0; i < numCells; i++)
		{
			notCollapsedIndexes[i] = i;
		}

		std::vector<int> lowestEntropyIndexes = std::vector<int>(numCells);
		int numLowestEntropy = 0;
		int lowestEntropy = INT_MAX;

		while (numCollapsed < numCells)
		{
			// Find lowest entropy indexes
			for (int i = 0; i < numCells - numCollapsed; i++)
			{
				int index = notCollapsedIndexes[i];
				WaveFunctionCollapseTile tile = tiles[index];

				if (tile.GetEntropy() == lowestEntropy)
				{
					lowestEntropyIndexes[numLowestEntropy] = index;
					numLowestEntropy++;
				}
				else if (tile.GetEntropy() < lowestEntropy)
				{
					lowestEntropyIndexes[0] = index;
					numLowestEntropy = 1;
				}
			}
		}
	}


	void WaveFunctionCollapseGrid::ClearGrid()
	{
		if (tiles == nullptr) return;

		delete tiles;
	}


	WaveFunctionCollapseTile* WaveFunctionCollapseGrid::GetTile(int x, int y)
	{
		return &(tiles[x + numCellsX * y]);
	}
}