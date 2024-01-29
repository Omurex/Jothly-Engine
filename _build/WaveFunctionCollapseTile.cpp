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


	void WaveFunctionCollapseTile::FilterPossibilities(WaveFunctionCollapseTile* northTile, WaveFunctionCollapseTile* eastTile, WaveFunctionCollapseTile* southTile, WaveFunctionCollapseTile* westTile)
	{
		if (possibilities.size() <= 0) return;

		/*std::string reverseNorthCode = GetNorthCode();
		std::reverse(reverseNorthCode.begin(), reverseNorthCode.end());

		std::string reverseEastCode = GetEastCode();
		std::reverse(reverseEastCode.begin(), reverseEastCode.end());

		std::string reverseSouthCode = GetSouthCode();
		std::reverse(reverseSouthCode.begin(), reverseSouthCode.end());

		std::string reverseWestCode = GetWestCode();
		std::reverse(reverseWestCode.begin(), reverseWestCode.end());*/

		std::vector<int> indexesToRemove = std::vector<int>(possibilities.size());
		int numIndexesToRemove = 0;

		// Optimize so we don't have to do null check every time
		for (int i = 0; i < possibilities.size(); i++)
		{
			bool compatible = true;

			WaveFunctionCollapseTile possibility = possibilities[i];

			if (northTile != nullptr && northTile->collapsed) compatible &= possibility.CompareCodes(TileDirection::NORTH, northTile->GetSouthCode());
			if (eastTile != nullptr && eastTile->collapsed) compatible &= possibility.CompareCodes(TileDirection::EAST, eastTile->GetWestCode());
			if (southTile != nullptr && southTile->collapsed) compatible &= possibility.CompareCodes(TileDirection::SOUTH, southTile->GetNorthCode());
			if (westTile != nullptr && westTile->collapsed) compatible &= possibility.CompareCodes(TileDirection::WEST, westTile->GetEastCode());

			if (compatible == false)
			{
				indexesToRemove.push_back(i);
				numIndexesToRemove++;
			}
		}

		for (int i = numIndexesToRemove - 1; i >= 0; i--)
		{
			// Not too optimized, probably just swap with back and then have separate count
			possibilities.erase(possibilities.begin() + indexesToRemove[i]);
		}
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


	bool WaveFunctionCollapseTile::CompareCodes(TileDirection dir, std::string otherCode)
	{
		std::reverse(otherCode.begin(), otherCode.end());
		return dirCodes[(int)dir] == otherCode;
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