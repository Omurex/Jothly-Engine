#include "ColorTestSet.h"
#include "Color.h"


namespace jothly
{
	void ColorTestSet::LoadTestFunctions()
	{
		testFunctions.push_back(ColorTest_Construction);
		testFunctions.push_back(ColorTest_Operations);
	}


	std::string ColorTestSet::GetTitle()
	{
		return "COLOR TESTS";
	}


	bool ColorTest_Construction(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Color Construction")

		rlb_Color col1 = rlb_Color(0.0f, .5f, .75f, 1.0f);
		rlb_Color col2 = rlb_Color(0, 127, 191, 255);

		AssertTest(col1 == col2, "Color Construction With Floats Error");

		return true;
	}


	bool ColorTest_Operations(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Color Operations")

		rlb_Color col1 = rlb_Color(0, 50, 100, 200);
		rlb_Color col2 = rlb_Color(50, 50, 50, 50);

		rlb_Color lerpResult = rlb_Color::Lerp(col1, col2, .25f);

		rlb_Color expectedLerpResult = rlb_Color(12, 50, 87, 162);

		AssertTest(lerpResult == expectedLerpResult, "Color Lerp Error")

		return true;
	}
}