#include "QuaternionTestSet.h"
#include "Quaternion.h"
#include "Math.h"
#include "Vector3.h"


namespace jothly
{
	void QuaternionTestSet::LoadTestFunctions()
	{
		testFunctions.push_back(QuaternionTest_Normalization);
		testFunctions.push_back(QuaternionTest_Rotation);
		testFunctions.push_back(QuaternionTest_Euler);
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
			0.5537176974307099f, 0.11096349603035f, -0.08608042118785003f, 0.8207765067437098f
		);

		int approxResult = Approx(q12.GetComponents(), q2.GetComponents(), 4);
		AssertTest(approxResult == 1, "Multiplication with Identity Error 1");

		approxResult = Approx(q21.GetComponents(), q2.GetComponents(), 4);
		AssertTest(approxResult == 1, "Multiplication with Identity Error 2");

		approxResult = Approx(q23.GetComponents(), expectedQ23, 4);
		AssertTest(approxResult == 1, "Multiplication Between Quaternions Error 1");

		approxResult = Approx(q32.GetComponents(), expectedQ32, 4);
		AssertTest(approxResult == 1, "Multiplication Between Quaternions Error 2")

		float temp;
		AssertTest(q12.IsNormalized(temp) * q21.IsNormalized(temp) * q23.IsNormalized(temp) * 
			q32.IsNormalized(temp) == 1, "Quaternion Multiplication Normal Result Error");

		return true;
	}


	bool QuaternionTest_Euler(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Euler");

		Vector3 eulerRad = Vector3(2.96706f, 1.0472f, 1.5708f); // 170, 60, 90
		Vector3 eulerDeg = Vector3(45, 135, -35);

		Quaternion qRad = Quaternion(eulerRad, false);
		Quaternion qDeg = Quaternion(eulerDeg);

		Vector4 expectedQRad = Vector4(0.5792263f, 0.640857f, -0.2988364f, 0.405581f);
		Vector4 expectedQDeg = Vector4(0.3963371f, 0.770011f, -0.4435054f, 0.2308743f);

		int approxResult = Approx(qRad.GetComponents(), expectedQRad, 4);
		AssertTest(approxResult == 1, "Quaternion Radians Euler To Components Error");
		
		approxResult = Approx(qDeg.GetComponents(), expectedQDeg, 4);
		AssertTest(approxResult == 1, "Quaternion Degrees Euler To Components Error");


		return true;
	}
}