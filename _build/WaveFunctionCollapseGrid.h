#pragma once


#include "Vector2.h"
#include "WaveFunctionCollapseTile.h"


namespace jothly
{
	class WaveFunctionCollapseGrid
	{
		WaveFunctionCollapseTile* tiles = nullptr;

		Vector2 topLeftPos;
		Vector2 gridSize; // NOT CELL NUMBER! PHYSICAL SIZE OF GRID

		int numCellsX;
		int numCellsY;

		
		public:

		WaveFunctionCollapseGrid(Vector2 _topLeftPos, Vector2 _gridSize)
		{
			SetTopLeftPos(_topLeftPos); SetGridSize(_gridSize);
		}


		void GenerateInitialGrid(int _numCellsX, int _numCellsY);
		void ClearGrid();

		void SetTopLeftPos(Vector2 _topLeftPos) { topLeftPos = _topLeftPos; }
		void SetGridSize(Vector2 _gridSize) { gridSize = _gridSize; }

		WaveFunctionCollapseTile& GetTile(int x, int y);
		Vector2 GetTopLeftPos() { return topLeftPos; }
		Vector2 GetGridSize() { return gridSize; }
		int GetNumCellsX() { return numCellsX; }
		int GetNumCellsY() { return numCellsY; }
	};
}