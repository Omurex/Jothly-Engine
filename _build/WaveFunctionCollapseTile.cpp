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
		tileSymmetry = other.tileSymmetry;
	}


	int WaveFunctionCollapseTile::GetEntropy()
	{
		return possibilities.size();
	}


	void WaveFunctionCollapseTile::FilterPossibilities(WaveFunctionCollapseTile* northTile, WaveFunctionCollapseTile* eastTile, WaveFunctionCollapseTile* southTile, WaveFunctionCollapseTile* westTile)
	{
		if (possibilities.size() <= 0) return;


		int ogPossibilities = possibilities.size();

		std::vector<int> indexesToRemove = std::vector<int>(possibilities.size());
		int numIndexesToRemove = 0;

		// Optimize so we don't have to do null check every time
		for (int i = 0; i < possibilities.size(); i++)
		{
			bool compatible = true;

			WaveFunctionCollapseTile& possibility = possibilities[i];

			if (northTile != nullptr && northTile->collapsed) compatible &= possibility.CompareCodes(TileDirection::NORTH, northTile->GetSouthCode());
			if (eastTile != nullptr && eastTile->collapsed) compatible &= possibility.CompareCodes(TileDirection::EAST, eastTile->GetWestCode());
			if (southTile != nullptr && southTile->collapsed) compatible &= possibility.CompareCodes(TileDirection::SOUTH, southTile->GetNorthCode());
			if (westTile != nullptr && westTile->collapsed) compatible &= possibility.CompareCodes(TileDirection::WEST, westTile->GetEastCode ());

			if (compatible == false)
			{
				indexesToRemove[numIndexesToRemove] = i;
				numIndexesToRemove++;
			}
		}

		if(numIndexesToRemove >= ogPossibilities)
			{//numIndexesToRemove++; // TEMP, REMOVE;
			int a = 0;
			a++;}

		for (int i = numIndexesToRemove - 1; i >= 0; i--)
		{
			// Not too optimized, probably just swap with back and then have separate count
			possibilities.erase(possibilities.begin() + indexesToRemove[i]);
		}

	}


	void WaveFunctionCollapseTile::LoadPossibilities(std::vector<WaveFunctionCollapseTile>& allPossibilities)
	{
		possibilities = std::vector<WaveFunctionCollapseTile>();
		possibilities.reserve(allPossibilities.size() * 4);

		for(int i = 0; i < allPossibilities.size(); i++)
		{
			possibilities.push_back(allPossibilities[i]);
			possibilities.back().SetRotation(TileRotation::ROT0);

			if(allPossibilities[i].tileSymmetry == TileSymmetry::FOUR_SIDED_SYMMETRIC) continue;

			possibilities.push_back(allPossibilities[i]);
			possibilities.back().SetRotation(TileRotation::ROT90);

			if(allPossibilities[i].tileSymmetry == TileSymmetry::TWO_SIDED_SYMMETRIC) continue;

			possibilities.push_back(allPossibilities[i]);
			possibilities.back().SetRotation(TileRotation::ROT180);

			possibilities.push_back(allPossibilities[i]);
			possibilities.back().SetRotation(TileRotation::ROT270);
		}
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

		Vector2 origin = size / 2.0f;
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

		TextureDrawing::DrawTexture(*texture, topLeftPos, origin, size, -rot);
	}


	bool WaveFunctionCollapseTile::CompareCodes(TileDirection dir, std::string otherCode)
	{
		std::reverse(otherCode.begin(), otherCode.end());
		return GetDirCodeRotated(dir) == otherCode;
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