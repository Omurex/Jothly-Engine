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

			std::string dirCodes[4];
		};


		WaveFunctionCollapseTile() {}
		~WaveFunctionCollapseTile() {}

		std::string GetDirCodeRotated(TileDirection dir);

		std::string GetNorthCode();
		std::string GetEastCode();
		std::string GetSouthCode();
		std::string GetWestCode();


		void DrawTile(Vector2 topLeftPos, Vector2 size);
	};
}