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


	void WaveFunctionCollapseGrid::InitializeGeneration()
	{
		// Find least entropy
		// Pick random fit given neighbors

		// Initialization
		numCells = numCellsX * numCellsY;
		notCollapsedIndexes = std::vector<int>(numCells);

		numCollapsed = 0;

		for (int i = 0; i < numCells; i++)
		{
			notCollapsedIndexes[i] = i;
		}

		lowestEntropyIndexes = std::vector<int>(numCells);
		notCollapsedIndexesLocations = std::vector<int>(numCells); // Used to keep track of where tile is in notCollapsedIndexes
	}

	
	void WaveFunctionCollapseGrid::Run()
	{
		while (numCollapsed < numCells && RunNextStep()) {}
	}


	bool WaveFunctionCollapseGrid::RunNextStep()
	{
		GenerateLowestEntropyList(lowestEntropyIndexes, notCollapsedIndexesLocations, numLowestEntropy);

 		WaveFunctionCollapseTile* collapsingTile = CollapseLowestEntropyTile();

		if (collapsingTile == nullptr || collapsingTile->GetIsCollapsed() == false) return false;

		PropagateFromTile(collapsingTile);

		return true;
	}


	int WaveFunctionCollapseGrid::GenerateLowestEntropyList(std::vector<int>& out_lowestEntropyIndexes, std::vector<int>& out_notCollapsedIndexesLocations, 
		int& out_numLowestEntropy)
	{
		int lowestEntropy = INT_MAX;
		out_numLowestEntropy = 0;

		// Find lowest entropy indexes
		for (int i = 0; i < numCells - numCollapsed; i++)
		{
			int index = notCollapsedIndexes[i];
			WaveFunctionCollapseTile* tile = tiles + index;

			int entropy = tile->GetEntropy();

			if (entropy == lowestEntropy)
			{
				out_lowestEntropyIndexes[numLowestEntropy] = index;
				out_notCollapsedIndexesLocations[numLowestEntropy] = i;

				out_numLowestEntropy++;
			}
			else if (entropy < lowestEntropy)
			{
				out_lowestEntropyIndexes[0] = index;
				out_notCollapsedIndexesLocations[0] = i;

				lowestEntropy = entropy;
				out_numLowestEntropy = 1;
			}
		}

		return lowestEntropy;
	}


	WaveFunctionCollapseTile* WaveFunctionCollapseGrid::CollapseLowestEntropyTile()
	{
		if(numLowestEntropy <= 0) return nullptr;

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
			return nullptr;
		}

		// Move tile index to the back of the notCollapsedIndexes array
		int backNotCollapsedIndex = (numCells - numCollapsed) - 1;
		int temp = notCollapsedIndexes[backNotCollapsedIndex];
		notCollapsedIndexes[backNotCollapsedIndex] = notCollapsedIndexes[notCollapsedIndex];
		notCollapsedIndexes[notCollapsedIndex] = temp;

		numCollapsed++;

		return collapsingTile;
	}


	void WaveFunctionCollapseGrid::PropagateFromTile(WaveFunctionCollapseTile* tile)
	{
		int originX = tile->GetX();
		int originY = tile->GetY();

		int largestDimension = numCellsX > numCellsY ? numCellsX : numCellsY;

		for(int radius = 1; radius <= largestDimension; radius++)
		{
			for(int x = -radius; x <= radius; x++)
			{
				int absX = abs(x);
				int yPos = radius - absX;
				int yNeg = -yPos;

				int worldX = originX + x;
				int worldYPos = originY + yPos;
				int worldYNeg = originY - yPos;

				WaveFunctionCollapseTile* tilePos = GetTile(worldX, worldYPos);
				WaveFunctionCollapseTile* tileNeg = GetTile(worldX, worldYNeg);


				if(tilePos != nullptr)
					tilePos->FilterPossibilities(GetTile(worldX, worldYPos - 1), GetTile(worldX + 1, worldYPos), GetTile(worldX, worldYPos + 1), GetTile(worldX - 1, worldYPos));


				if (tileNeg != nullptr)
					tileNeg->FilterPossibilities(GetTile(worldX, worldYNeg - 1), GetTile(worldX + 1, worldYNeg), GetTile(worldX, worldYNeg + 1), GetTile(worldX - 1, worldYNeg));

				//if(x == -radius) // Only filter based on east tile
				//{
				//	if(tilePos == nullptr) continue; // TODO: Refactor so we don't have so many of these

				//	tilePos->FilterPossibilities(nullptr, GetTile(worldX + 1, worldYPos), nullptr, nullptr);
				//	continue;
				//}
				//
				//if(x == radius) // Only filter based on west tile
				//{
				//	if (tilePos == nullptr) continue; // TODO: Refactor so we don't have so many of these

				//	tilePos->FilterPossibilities(nullptr, nullptr, nullptr, GetTile(worldX - 1, worldYPos));
				//	continue;
				//}

				//if(yPos == radius) // Only filter based on south tile for yPos and north for yNeg
				//{
				//	if (tilePos != nullptr)
				//	{
				//		tilePos->FilterPossibilities(GetTile(worldX, worldYPos - 1), nullptr, nullptr, nullptr);
				//		//tilePos->FilterPossibilities(nullptr, nullptr, GetTile(worldX, worldYPos + 1), nullptr);
				//	}

				//	if(tileNeg != nullptr)
				//	{
				//		tileNeg->FilterPossibilities(nullptr, nullptr, GetTile(worldX, worldYNeg + 1), nullptr);
				//		//tileNeg->FilterPossibilities(GetTile(worldX, worldYNeg - 1), nullptr, nullptr, nullptr);
				//	}

				//	continue;
				//}

				//if(x < 0)
				//{
				//	if (tilePos != nullptr)
				//		tilePos->FilterPossibilities(GetTile(worldX, worldYPos - 1), GetTile(worldX + 1, worldYPos), nullptr, nullptr);
				//		//tilePos->FilterPossibilities(nullptr, GetTile(worldX + 1, worldYPos),)

				//	if (tileNeg != nullptr)
				//		tileNeg->FilterPossibilities(nullptr, GetTile(worldX + 1, worldYPos), GetTile(worldX, worldYNeg + 1), nullptr);
				//}
				//else
				//{
				//	if (tilePos != nullptr)
				//		tilePos->FilterPossibilities(GetTile(worldX, worldYPos - 1), nullptr, nullptr, GetTile(worldX - 1, worldYPos));
				//	
				//	if(tileNeg != nullptr)
				//		tileNeg->FilterPossibilities(nullptr, nullptr, GetTile(worldX, worldYNeg + 1), GetTile(worldX - 1, worldYNeg));
				//}
			}

		}

		/*if (GetTile(originX, originY - 1))
			GetTile(originX, originY - 1)->FilterPossibilities(GetTile(originX, originY - 2), GetTile(originX + 1, originY - 1), GetTile(originX, originY), GetTile(originX - 1, originY - 1));
		if (GetTile(originX, originY + 1))
			GetTile(originX, originY + 1)->FilterPossibilities(GetTile(originX, originY), GetTile(originX + 1, originY + 1), GetTile(originX, originY + 1), GetTile(originX - 1, originY + 1));
		if (GetTile(originX + 1, originY))
			GetTile(originX + 1, originY)->FilterPossibilities(GetTile(originX + 1, originY - 1), GetTile(originX + 2, originY), GetTile(originX + 1, originY + 1), GetTile(originX, originY));
		if (GetTile(originX - 1, originY))
			GetTile(originX - 1, originY)->FilterPossibilities(GetTile(originX - 1, originY - 1), GetTile(originX, originY), GetTile(originX - 1, originY + 1), GetTile(originX - 2, originY));*/

		/*for (int i = 0; i < numCells - numCollapsed; i++)
		{
			WaveFunctionCollapseTile* tile = tiles + notCollapsedIndexes[i];

			int x = tile->GetX();
			int y = tile->GetY();

			tile->FilterPossibilities(GetTile(x, y - 1), GetTile(x + 1, y), GetTile(x, y + 1), GetTile(x - 1, y));
		}*/
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

		return tiles + (x + numCellsX * y);
	}
}