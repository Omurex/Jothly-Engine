#pragma once


#include "Vector2.h"
#include "WaveFunctionCollapseTile.h"


namespace jothly
{
	class WaveFunctionCollapseGrid
	{
		//WaveFunctionCollapseTile tiles[][] jo;

		Vector2 topLeftPos;
		Vector2 gridSize; // NOT CELL NUMBER! PHYSICAL SIZE OF GRID

		int numCellsX;
		int numCellsY;

		
		WaveFunctionCollapseGrid(Vector2 _topLeftPos, Vector2 _gridSize, int _numCellsX, int _numCellsY) 
		{
			SetTopLeftPos(_topLeftPos); SetGridSize(_gridSize); SetNumCellsX(_numCellsX); SetNumCellsY(_numCellsY);
		}

		void SetTopLeftPos(Vector2 _topLeftPos) { topLeftPos = _topLeftPos; }
		void SetGridSize(Vector2 _gridSize) { gridSize = _gridSize; }
		void SetNumCellsX(int _numCellsX) { numCellsX = _numCellsX; }
		void SetNumCellsY(int _numCellsY) { numCellsY = _numCellsY; }

		Vector2 GetTopLeftPos() { return topLeftPos; }
		Vector2 GetGridSize() { return gridSize; }
		int GetNumCellsX() { return numCellsX; }
		int GetNumCellsY() { return numCellsY; }
	};
}