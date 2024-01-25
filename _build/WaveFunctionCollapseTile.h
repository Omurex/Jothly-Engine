#pragma once

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


	struct WaveFunctionCollapseTile
	{
		Texture texture;
		
		int x;
		int y;

		TileRotation tileRotation;


		void DrawTile(Vector2 topLeftPos, Vector2 size);
	};
}