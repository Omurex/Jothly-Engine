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

		return true;
	}


	bool ColorTest_Operations(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Color Operations")

		return true;
	}
}