#include "WaveFunctionCollapseTile.h"
#include "TextureDrawing.h"
#include <assert.h>
#include <string>
#include <unordered_set>


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

		std::unordered_set<std::string> northTileSouthCodes;
		std::unordered_set<std::string> eastTileWestCodes;
		std::unordered_set<std::string> southTileNorthCodes;
		std::unordered_set<std::string> westTileEastCodes;


		if (northTile != nullptr && northTile->collapsed == false)
		{
			for (int i = 0; i < northTile->possibilities.size(); i++)
			{
				northTileSouthCodes.insert(northTile->possibilities[i].GetSouthCode());
			}
		}

		if (eastTile != nullptr && eastTile->collapsed == false)
		{
			for (int i = 0; i < eastTile->possibilities.size(); i++)
			{
				eastTileWestCodes.insert(eastTile->possibilities[i].GetWestCode());
			}
		}

		if (southTile != nullptr && southTile->collapsed == false)
		{
			for (int i = 0; i < southTile->possibilities.size(); i++)
			{
				southTileNorthCodes.insert(southTile->possibilities[i].GetNorthCode());
			}
		}

		if (westTile != nullptr && westTile->collapsed == false)
		{
			for (int i = 0; i < westTile->possibilities.size(); i++)
			{
				westTileEastCodes.insert(westTile->possibilities[i].GetEastCode());
			}
		}


		for (int i = possibilities.size() - 1; i >= 0; i--)
		{
			//std::string possibilityWest = possibility

			std::string nRev = possibilities[i].GetNorthCode();
			std::reverse(nRev.begin(), nRev.end());

			std::string eRev = possibilities[i].GetEastCode();
			std::reverse(eRev.begin(), eRev.end());

			std::string sRev = possibilities[i].GetSouthCode();
			std::reverse(sRev.begin(), sRev.end());

			std::string wRev = possibilities[i].GetWestCode();
			std::reverse(wRev.begin(), wRev.end());

			bool possibilityPossible =
				(northTileSouthCodes.size() == 0 || northTileSouthCodes.find(nRev) != northTileSouthCodes.end()) &&
				(eastTileWestCodes.size() == 0 || eastTileWestCodes.find(eRev) != eastTileWestCodes.end()) &&
				(southTileNorthCodes.size() == 0 || southTileNorthCodes.find(sRev) != southTileNorthCodes.end()) &&
				(westTileEastCodes.size() == 0 || westTileEastCodes.find(wRev) != westTileEastCodes.end());

			if (!possibilityPossible)
			{
				possibilities.erase(possibilities.begin() + i);
			}
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