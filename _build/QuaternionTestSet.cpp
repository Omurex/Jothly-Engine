#include "QuaternionTestSet.h"
#include "Quaternion.h"
#include "Math.hpp"


namespace jothly
{
	void QuaternionTestSet::LoadTestFunctions()
	{
		testFunctions.push_back(QuaternionTest_CoreFunctionality);
	}


	std::string QuaternionTestSet::GetTitle()
	{
		return "QUATERNION TESTS";
	}


	bool QuaternionTest_CoreFunctionality(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Core Functionality");

		Quaternion q1 = Quaternion(Vector4(8, 1, 1, 1));
		q1 = q1.GetNormalized();
		float magSquared = q1.GetComponents().GetMagnitudeSquared();
		AssertTest(Approx(magSquared, 1) == 1, "Quaternion Normalization Error");

		return true;
	}
}