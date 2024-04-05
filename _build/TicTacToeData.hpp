#pragma once


namespace jothly
{
	static const int TTT_NUM_SPACES = 9;

	enum TTTSquare : char
	{
		EMPTY,
		X,
		O
	};

	enum TTTResult : int
	{
		STILL_PLAYING,
		X_WIN,
		O_WIN,
		DRAW
	};
}