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

		Color col1 = Color(0.0f, .5f, .75f, 1.0f);
		Color col2 = Color(0, 127, 191, 255);

		AssertTest(col1 == col2, "Color Construction With Floats Error");

		return true;
	}


	bool ColorTest_Operations(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Color Operations")

		Color col1 = Color(0, 50, 100, 200);
		Color col2 = Color(50, 50, 50, 50);

		Color lerpResult = Color::Lerp(col1, col2, .25f);

		Color expectedLerpResult = Color(12, 50, 87, 162);

		AssertTest(lerpResult == expectedLerpResult, "Color Lerp Error")

		return true;
	}
}