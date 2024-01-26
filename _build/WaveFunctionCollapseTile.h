#pragma once

#include <string>
#include "Texture.h"


namespace jothly
{
	enum class TileRotation
	{
		ROT0,
		ROT90,
		ROT180,
		ROT270
	};


	enum class TileDirection
	{
		UP = 0,
		RIGHT = 1,
		DOWN = 2,
		LEFT = 3
	};


	struct WaveFunctionCollapseTile
	{
		Texture* texture;
		TileRotation tileRotation;

		union
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

		void DrawTile(Vector2 topLeftPos, Vector2 size);
	};
}