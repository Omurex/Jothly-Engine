#pragma once

#include <string>
#include "Texture.h"


namespace jothly
{
	enum class TileRotation
	{
		ROT0 = 0,
		ROT90 = 1,
		ROT180 = 2,
		ROT270 = 3
	};


	enum class TileDirection
	{
		NORTH = 0,
		EAST = 1,
		SOUTH = 2,
		WEST = 3
	};


	enum class TileSymmetry
	{
		NOT_SYMMETRIC,
		TWO_SIDED_SYMMETRIC,
		FOUR_SIDED_SYMMETRIC
	};


	struct WaveFunctionCollapseTile
	{
		private:

		// What tiles this could possibly collapse down to
		std::vector<WaveFunctionCollapseTile> possibilities = std::vector<WaveFunctionCollapseTile>();
		TileRotation tileRotation = TileRotation::ROT0;
		TileSymmetry tileSymmetry = TileSymmetry::NOT_SYMMETRIC;

		bool collapsed = false;
		int x = -1;
		int y = -1;

		void Copy(const WaveFunctionCollapseTile& other);

		public:
		Texture* texture = nullptr;

		union // These are based on 0 rotation!
		{
			struct
			{
				std::string upCode;
				std::string rightCode;
				std::string downCode;
				std::string leftCode;
			};

			std::string dirCodes[4] { "", "", "", "" };
		};


		WaveFunctionCollapseTile() : upCode(""), rightCode(""), downCode(""), leftCode("") {}

		WaveFunctionCollapseTile(const WaveFunctionCollapseTile& other) { Copy(other); }

		WaveFunctionCollapseTile(Texture* _texture, std::string _upCode, std::string _rightCode, std::string _downCode, std::string _leftCode, TileSymmetry _tileSymmetry = TileSymmetry::NOT_SYMMETRIC) :
			texture(_texture), upCode(_upCode), rightCode(_rightCode), downCode(_downCode), leftCode(_leftCode), tileSymmetry(_tileSymmetry) {}

		~WaveFunctionCollapseTile() {}


		void SetCoordinates(int _x, int _y) { x = _x; y = _y; }
		void SetRotation(TileRotation _tileRotation) { tileRotation = _tileRotation; }


		std::string GetDirCodeRotated(TileDirection dir );

		std::string GetNorthCode();
		std::string GetEastCode();
		std::string GetSouthCode();
		std::string GetWestCode();

		TileRotation GetRotation() { return tileRotation; }

		int GetEntropy();
		bool GetIsCollapsed() { return collapsed; }

		int GetX() { return x; }
		int GetY() { return y; }

		bool CompareCodes(TileDirection dir, std::string otherCode);


		void FilterPossibilities(WaveFunctionCollapseTile* northTile, WaveFunctionCollapseTile* eastTile, WaveFunctionCollapseTile* southTile, WaveFunctionCollapseTile* westTile);


		bool Collapse();
		void LoadPossibilities(std::vector<WaveFunctionCollapseTile>& allPossibilities);


		void DrawTile(Vector2 topLeftPos, Vector2 size);

		WaveFunctionCollapseTile& operator=(const WaveFunctionCollapseTile& other) { Copy(other); return *this; }
	};
}