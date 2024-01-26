#pragma once


#include "Vector2.h"
#include "WaveFunctionCollapseTile.h"
#include "Component.h"


namespace jothly
{
	class WaveFunctionCollapseGrid : public Component
	{
		friend class GameObject;


		WaveFunctionCollapseTile* tiles = nullptr;

		Vector2 offset;
		Vector2 gridSize; // NOT CELL NUMBER! PHYSICAL SIZE OF GRID

		int numCellsX = 0;
		int numCellsY = 0;

		
		WaveFunctionCollapseGrid(GameObject* _owner) : Component(_owner) {}


		void Draw() override;


		public:
		ComponentID GetID() const { return ComponentID::WAVE_FUNCTION_COLLAPSE_GRID; }


		WaveFunctionCollapseGrid* Init(Vector2 _offset, Vector2 _gridSize);


		void GenerateInitialGrid(int _numCellsX, int _numCellsY);
		void ClearGrid();

		void SetOffset(Vector2 _offset) { offset = _offset; }
		void SetGridSize(Vector2 _gridSize) { gridSize = _gridSize; }

		WaveFunctionCollapseTile* GetTile(int x, int y);
		Vector2 GetOffset() { return offset; }
		Vector2 GetGridSize() { return gridSize; }
		int GetNumCellsX() { return numCellsX; }
		int GetNumCellsY() { return numCellsY; }
	};
}