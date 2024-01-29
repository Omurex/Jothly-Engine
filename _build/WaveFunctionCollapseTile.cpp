#include "WaveFunctionCollapseTile.h"
#include "TextureDrawing.h"
#include <assert.h>


namespace jothly
{
	void WaveFunctionCollapseTile::Copy(const WaveFunctionCollapseTile& other)
	{
		texture = other.texture;
		tileRotation = other.tileRotation;
		upCode = other.upCode;
		rightCode = other.rightCode;
		downCode = other.downCode;
		leftCode = other.leftCode;
	}


	int WaveFunctionCollapseTile::GetEntropy()
	{
		return possibilities.size();
	}


	void WaveFunctionCollapseTile::LoadPossibilities(std::vector<WaveFunctionCollapseTile>& allPossibilities)
	{
		possibilities = std::vector<WaveFunctionCollapseTile>(allPossibilities);
	}


	bool WaveFunctionCollapseTile::Collapse()
	{
		if (possibilities.size() <= 0) return false;

		int index = rand() % possibilities.size();
		Copy(possibilities[index]);
		collapsed = true;

		return true;


	}


	void WaveFunctionCollapseTile::DrawTile(Vector2 topLeftPos, Vector2 size)
	{
		if (texture == nullptr) return;

		Vector2 origin = (texture->GetSize()) / 2.0f;
		float rot = 0;

		switch (tileRotation)
		{
			case TileRotation::ROT90:
			{
				rot = 90;
				break;
			}

			case TileRotation::ROT180:
			{
				rot = 180;
				break;
			}

			case TileRotation::ROT270:
			{
				rot = 270;
				break;
			}
		}

		TextureDrawing::DrawTexture(*texture, topLeftPos, origin, size, rot);
	}


	std::string WaveFunctionCollapseTile::GetDirCodeRotated(TileDirection dir)
	{
		return dirCodes[((int) dir + (int)tileRotation) % 4];
	}


	std::string WaveFunctionCollapseTile::GetNorthCode()
	{
		return GetDirCodeRotated(TileDirection::NORTH);
	}


	std::string WaveFunctionCollapseTile::GetEastCode()
	{
		return GetDirCodeRotated(TileDirection::EAST);
	}


	std::string WaveFunctionCollapseTile::GetSouthCode()
	{
		return GetDirCodeRotated(TileDirection::SOUTH);
	}


	std::string WaveFunctionCollapseTile::GetWestCode()
	{
		return GetDirCodeRotated(TileDirection::WEST);
	}
}