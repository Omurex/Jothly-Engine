#include "QuaternionTestSet.h"
#include "Quaternion.h"
#include "Math.hpp"


namespace jothly
{
	void QuaternionTestSet::LoadTestFunctions()
	{
		testFunctions.push_back(QuaternionTest_CoreFunctionality);
	}


	bool QuaternionTest_CoreFunctionality(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Core Functionality");

		Quaternion q1 = Quaternion(Vector4(8, 1, 1, 1));
		q1 = q1.GetNormalized();
		AssertTest(Approx(q1.GetComponents().GetMagnitudeSquared(), 1) == 1, "Quaternion Normalization Error");

		return true;
	}
}