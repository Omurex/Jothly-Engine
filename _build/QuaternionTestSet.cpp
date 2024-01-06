#include "QuaternionTestSet.h"
#include "Quaternion.h"
#include "Math.h"
#include "Vector3.h"


namespace jothly
{
	void QuaternionTestSet::LoadTestFunctions()
	{
		testFunctions.push_back(QuaternionTest_Normalization);
		testFunctions.push_back(QuaternionTest_Euler);
		testFunctions.push_back(QuaternionTest_FromAngleAxis);
		testFunctions.push_back(QuaternionTest_QuaternionRotation);
	}


	std::string QuaternionTestSet::GetTitle()
	{
		return "QUATERNION TESTS";
	}


	bool QuaternionTest_Normalization(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Core Functionality");

		Vector4(1, 1, 1, 1).GetMagnitudeSquared();

		Quaternion q1 = Quaternion(Vector4(8, 1, 1, 1));
		q1 = q1.GetNormalized();
		float magSquared = q1.GetComponents().GetMagnitudeSquared();

		AssertTest(Approx(magSquared, 1) == 1, "Quaternion Normalization Error");
		AssertTest(q1.IsNormalized(magSquared), "Quaternion IsNormalized Error");
		AssertTest(Approx(magSquared, 1) == 1, "Quaternion IsNormalized Output Error");

		return true;
	}

	
	bool QuaternionTest_QuaternionRotation(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Rotation");

		Quaternion q1 = Quaternion::Identity();

		// Euler: x = 90, y = 90, z = 45
		// 0.6532815f, 0.2705981f, 0.6532815f, 0.2705981f
		Quaternion q2 = Quaternion(Vector3(90, 90, 45));

		// Euler: x = -30, y = 60, z = -80
		Quaternion q3 = Quaternion(Vector3(-30, 60, -80));

		Quaternion q12 = q1 * q2;
		Quaternion q21 = q2 * q1;
		Quaternion q23 = q2 * q3;
		Quaternion q32 = q3 * q2;

		Vector4 expectedQ23 = Vector4(
			0.1391373f, 0.8899217f, -0.4339544f, -0.01906598f
		);

		Vector4 expectedQ32 = Vector4(
			0.4339544f, 0.7276547f, -0.5308846f, -0.01906598f
		);

		int approxResult = Approx(q12.GetComponents(), q2.GetComponents());
		AssertTest(approxResult == 1, "Multiplication with Identity Error 1");

		approxResult = Approx(q21.GetComponents(), q2.GetComponents());
		AssertTest(approxResult == 1, "Multiplication with Identity Error 2");

		approxResult = Approx(q23.GetComponents(), expectedQ23);
		AssertTest(approxResult == 1, "Multiplication Between Quaternions Error 1");

		approxResult = Approx(q32.GetComponents(), expectedQ32);
		AssertTest(approxResult == 1, "Multiplication Between Quaternions Error 2")

		float temp;
		AssertTest(q12.IsNormalized(temp) * q21.IsNormalized(temp) * q23.IsNormalized(temp) * 
			q32.IsNormalized(temp) == 1, "Quaternion Multiplication Normal Result Error");

		return true;
	}


	bool QuaternionTest_Euler(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Euler");

		Vector3 eulerRad = Vector3(2.96706f, 1.0472f, -1.5708f); // 170, 60, 90
		Vector3 eulerDeg = Vector3(45, 135, -35);

		Quaternion qRad = Quaternion(eulerRad, false);
		Quaternion qDeg = Quaternion(eulerDeg);

		Vector4 expectedQRad = Vector4(0.6408549f, -0.5792287f, -0.4055799f, -0.2988379f);
		Vector4 expectedQDeg = Vector4(0.3963371f, 0.770011f, -0.4435054f, 0.2308743f);

		int approxResult = Approx(qRad.GetComponents(), expectedQRad);
		AssertTest(approxResult == 1, "Quaternion Radians Euler To Components Error");
		
		approxResult = Approx(qDeg.GetComponents(), expectedQDeg);
		AssertTest(approxResult == 1, "Quaternion Degrees Euler To Components Error");

		return true;
	}

	
	bool QuaternionTest_FromAngleAxis(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion From Angle Axis");

		Quaternion q1NoAngle = Quaternion(0, Vector3(1, 0, 0));
		Quaternion q2NoAngle = Quaternion(0, Vector3(-.3f, .5f, .5f));
		Quaternion q3NoAngle = Quaternion(0, Vector3(0, 0, 0));

		Quaternion q1 = Quaternion(60, Vector3(1, 0, 0));
		Quaternion q2 = Quaternion(60, Vector3(-.3f, .5f, .5f));
		Quaternion q3 = Quaternion(60, Vector3(0, 0, 0));

		Quaternion q4 = Quaternion(160, Vector3(1, 1, -1));
		Quaternion q5 = Quaternion(270, Vector3(1, 1, -1));
		Quaternion q6 = Quaternion(273, Vector3(1, 1, -1));

		Quaternion q7 = Quaternion(-30, Vector3(1, 1, -1));
		Quaternion q8 = Quaternion(180, Vector3(1, 1, -1));
		Quaternion q9 = Quaternion(-350, Vector3(1, 1, -1));


		int approxResult = Approx(q1NoAngle.GetComponents(), Vector4(0, 0, 0, 1));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: No Angle 1");

		approxResult = Approx(q2NoAngle.GetComponents(), Vector4(0, 0, 0, 1));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: No Angle 2");

		approxResult = Approx(q3NoAngle.GetComponents(), Vector4(0, 0, 0, 1));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: No Angle 3");


		approxResult = Approx(q1.GetComponents(), Vector4(0.5f, 0, 0, 0.8660254f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q1");

		approxResult = Approx(q2.GetComponents(), Vector4(-0.1952834f, 0.3254723f, 0.3254723f, 0.8660254f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q2");

		approxResult = Approx(q3.GetComponents(), Vector4(0, 0, 0, 1));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q3");


		approxResult = Approx(q4.GetComponents(), Vector4(0.568579f, 0.568579f, -0.568579f, 0.1736482f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q4");

		approxResult = Approx(q5.GetComponents(), Vector4(0.4082483f, 0.4082483f, -0.4082483f, -0.7071068f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q5");

		approxResult = Approx(q6.GetComponents(), Vector4(0.3974217f, 0.3974217f, -0.3974217f, -0.7253744f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q6");


		approxResult = Approx(q7.GetComponents(), Vector4(-0.1494292f, -0.1494292f, 0.1494292f, 0.9659258f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q7");

		approxResult = Approx(q8.GetComponents(), Vector4(0.5773503f, 0.5773503f, -0.5773503f, 0.f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q8");

		approxResult = Approx(q9.GetComponents(), Vector4(-0.0503194f, -0.0503194f, 0.0503194f, -0.9961947f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q9");


		return true;
	}
}