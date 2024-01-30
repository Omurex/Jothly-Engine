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
				WaveFunctionCollapseTile* tile = GetTile(x, y);
				tile->SetCoordinates(x, y);
				tile->LoadPossibilities(templateTiles);
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
		std::vector<int> notCollapsedIndexesLocations = std::vector<int>(numCells); // Used to keep track of where tile is in notCollapsedIndexes

		while (numCollapsed < numCells)
		{
			int numLowestEntropy = 0;
			int lowestEntropy = INT_MAX;

			// Find lowest entropy indexes
			for (int i = 0; i < numCells - numCollapsed; i++)
			{
				int index = notCollapsedIndexes[i];
				WaveFunctionCollapseTile* tile = tiles + index;

				int entropy = tile->GetEntropy();

				if (entropy == lowestEntropy)
				{
					lowestEntropyIndexes[numLowestEntropy] = index;
					notCollapsedIndexesLocations[numLowestEntropy] = i;

					numLowestEntropy++;
				}
				else if (entropy < lowestEntropy)
				{
					lowestEntropyIndexes[0] = index;
					notCollapsedIndexesLocations[0] = i;

					lowestEntropy = entropy;
					numLowestEntropy = 1;
				}
			}

			// Pick random from lowest entropy
			int arrIndex = rand() % numLowestEntropy;
			int tileIndex = lowestEntropyIndexes[arrIndex];
			int notCollapsedIndex = notCollapsedIndexesLocations[arrIndex];

			WaveFunctionCollapseTile* collapsingTile = tiles + tileIndex;
			collapsingTile->Collapse();

			if (collapsingTile->GetIsCollapsed() == false)
			{
				/*GenerateInitialGrid(numCellsX, numCellsY);
				Run();*/
				return;
			}

			// Move tile index to the back of the notCollapsedIndexes array
			int backNotCollapsedIndex = (numCells - numCollapsed) - 1;
			int temp = notCollapsedIndexes[backNotCollapsedIndex];
			notCollapsedIndexes[backNotCollapsedIndex] = notCollapsedIndexes[notCollapsedIndex];
			notCollapsedIndexes[notCollapsedIndex] = temp;

			numCollapsed++;

			int x = collapsingTile->GetX();
			int y = collapsingTile->GetY();

			/*if(GetTile(x, y - 1))
				GetTile(x, y - 1)->FilterPossibilities(GetTile(x, y - 2), GetTile(x + 1, y - 1), GetTile(x, y), GetTile(x - 1, y - 1));
			if (GetTile(x, y + 1))
				GetTile(x, y + 1)->FilterPossibilities(GetTile(x, y), GetTile(x + 1, y + 1), GetTile(x, y + 1), GetTile(x - 1, y + 1));
			if (GetTile(x + 1, y))
				GetTile(x + 1, y)->FilterPossibilities(GetTile(x + 1, y - 1), GetTile(x + 2, y), GetTile(x + 1, y + 1), GetTile(x, y));
			if (GetTile(x - 1, y))
				GetTile(x - 1, y)->FilterPossibilities(GetTile(x - 1, y - 1), GetTile(x, y), GetTile(x - 1, y + 1), GetTile(x - 2, y));*/

			for (int i = 0; i < numCells - numCollapsed; i++)
			{
				WaveFunctionCollapseTile* tile = tiles + notCollapsedIndexes[i];
				
				int x = tile->GetX();
				int y = tile->GetY();

				tile->FilterPossibilities(GetTile(x, y - 1), GetTile(x + 1, y), GetTile(x, y + 1), GetTile(x - 1, y));
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
		// Cell does not exist!
		if (x < 0 || x >= numCellsX || y < 0 || y >= numCellsY) return nullptr;

		return &(tiles[x + numCellsX * y]);
	}
}