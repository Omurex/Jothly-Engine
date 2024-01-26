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
				//topLeftPos += GetTile(x, y)->texture->GetSize() / 2;
				topLeftPos += owner->transform.pos;
				topLeftPos += offset;
				GetTile(x, y)->DrawTile(topLeftPos, tileSize);
			}
		}
	}


	WaveFunctionCollapseGrid* WaveFunctionCollapseGrid::Init(Vector2 _offset, Vector2 _gridSize)
	{
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
				tiles[x + numCellsX * y] = WaveFunctionCollapseTile();
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