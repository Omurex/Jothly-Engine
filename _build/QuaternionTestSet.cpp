#include "QuaternionTestSet.h"
#include "Quaternion.h"
#include "Math.hpp"


namespace jothly
{
	void QuaternionTestSet::LoadTestFunctions()
	{
		testFunctions.push_back(QuaternionTest_Normalization);
		testFunctions.push_back(QuaternionTest_Rotation);
	}


	std::string QuaternionTestSet::GetTitle()
	{
		return "QUATERNION TESTS";
	}


	bool QuaternionTest_Normalization(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Core Functionality");

		Quaternion q1 = Quaternion(Vector4(8, 1, 1, 1));
		q1 = q1.GetNormalized();
		float magSquared = q1.GetComponents().GetMagnitudeSquared();

		AssertTest(Approx(magSquared, 1) == 1, "Quaternion Normalization Error");
		AssertTest(q1.IsNormalized(magSquared), "Quaternion IsNormalized Error");
		AssertTest(Approx(magSquared, 1) == 1, "Quaternion IsNormalized Output Error");

		return true;
	}

	
	bool QuaternionTest_Rotation(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Rotation");

		Quaternion q1 = Quaternion::Identity();

		// Euler: x = 90, y = 90, z = 45
		Quaternion q2 = Quaternion(0.6532815f, 0.2705981f, 0.6532815f, 0.2705981f);

		// Euler: x = -30, y = 60, z = -80
		Quaternion q3 = Quaternion(-0.4821467f, 0.2258942f, -0.6368358f, 0.5576258f);

		Quaternion q12 = q1 * q2;
		Quaternion q21 = q2 * q1;
		Quaternion q23 = q2 * q3;
		Quaternion q32 = q3 * q2;

		Vector4 expectedQ23 = Vector4(
			-0.08608042118785003f, 0.31307455059365f, 0.4700005443292899f, 0.8207765067437098f
		);

		Vector4 expectedQ32 = Vector4(
			0.5537176974307099, 0.11096349603035, -0.08608042118785003, 0.8207765067437098
		);

		int approxResult = Approx(q12.GetComponents(), q2.GetComponents(), 4, .001f);
		AssertTest(approxResult == 1, "Multiplication with Identity Error 1");

		approxResult = Approx(q21.GetComponents(), q2.GetComponents(), 4, .001f);
		AssertTest(approxResult == 1, "Multiplication with Identity Error 2");

		approxResult = Approx(q23.GetComponents(), expectedQ23, 4, .001f);
		AssertTest(approxResult == 1, "Multiplication Between Quaternions Error 1");

		approxResult = Approx(q32.GetComponents(), expectedQ32, 4, .001f);
		AssertTest(approxResult == 1, "Multiplication Between Quaternions Error 2")

		float temp;
		AssertTest(q12.IsNormalized(temp) * q21.IsNormalized(temp) * q23.IsNormalized(temp) * 
			q32.IsNormalized(temp) == 1, "Quaternion Multiplication Normal Result Error");

		return true;
	}
}