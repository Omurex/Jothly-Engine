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


	struct WaveFunctionCollapseTile
	{
		private:
		void Copy(const WaveFunctionCollapseTile& other);

		// What tiles this could possibly collapse down to
		std::vector<WaveFunctionCollapseTile> possibilities = std::vector<WaveFunctionCollapseTile>();

		bool collapsed = false;
		int x = -1;
		int y = -1;


		public:
		Texture* texture = nullptr;
		TileRotation tileRotation = TileRotation::ROT0;

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

		WaveFunctionCollapseTile(Texture* _texture, TileRotation _tileRotation, std::string _upCode, std::string _rightCode, std::string _downCode, std::string _leftCode) :
			texture(_texture), tileRotation(_tileRotation), upCode(_upCode), rightCode(_rightCode), downCode(_downCode), leftCode(_leftCode) {}

		~WaveFunctionCollapseTile() {}


		void SetCoordinates(int _x, int _y) { x = _x; y = _y; }


		std::string GetDirCodeRotated(TileDirection dir );

		std::string GetNorthCode();
		std::string GetEastCode();
		std::string GetSouthCode();
		std::string GetWestCode();

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