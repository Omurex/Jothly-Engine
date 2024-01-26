#pragma once


#include "Vector2.h"


namespace jothly
{
	class WaveFunctionCollapseGrid
	{
		Vector2 topLeftPos;
		Vector2 gridSize; // NOT CELL NUMBER! PHYSICAL SIZE OF GRID

		int numCellsX;
		int numCellsY;

		
		WaveFunctionCollapseGrid(Vector2 _topLeftPos, Vector2 _gridSize, int _numCellsX, int _numCellsY) {}


		Vector2 GetTopLeftPos() { return topLeftPos; }
		Vector2 GetGridSize() { return gridSize; }
		int GetNumCellsX() { return numCellsX; }
		int GetNumCellsY() { return numCellsY; }
	};
}