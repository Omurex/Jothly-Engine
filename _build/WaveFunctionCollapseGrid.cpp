#include "WaveFunctionCollapseGrid.h"


namespace jothly
{
	void WaveFunctionCollapseGrid::GenerateInitialGrid(int width, int height)
	{
		ClearGrid();

		tiles = new WaveFunctionCollapseTile[width * height];
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				tiles[x + width * y] = WaveFunctionCollapseTile();
			}
		}
	}


	void WaveFunctionCollapseGrid::ClearGrid()
	{
		if (tiles == nullptr) return;

		delete tiles;
	}


	WaveFunctionCollapseTile& WaveFunctionCollapseGrid::GetTile(int x, int y)
	{
		return tiles[x + numCellsX * y];
	}
}