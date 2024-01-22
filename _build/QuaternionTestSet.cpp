#include "QuaternionTestSet.h"
#include "Quaternion.h"
#include "Math.h"
#include "Vector3.h"
#include "Vector2.h"


namespace jothly
{
	void QuaternionTestSet::LoadTestFunctions()
	{
		testFunctions.push_back(QuaternionTest_Normalization);
		testFunctions.push_back(QuaternionTest_Euler);
		testFunctions.push_back(QuaternionTest_FromAngleAxis);
		testFunctions.push_back(QuaternionTest_QuaternionRotation);
		testFunctions.push_back(QuaternionTest_Inverse);
		testFunctions.push_back(QuaternionTest_VectorRotation);
		testFunctions.push_back(QuaternionTest_2D);
	}


	std::string QuaternionTestSet::GetTitle()
	{
		return "QUATERNION TESTS";
	}


	bool QuaternionTest_Normalization(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Core Functionality");

		rlb_Vector4(1, 1, 1, 1).GetMagnitudeSquared();

		rlb_Quaternion q1 = rlb_Quaternion(rlb_Vector4(8, 1, 1, 1));
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

		rlb_Quaternion q1 = rlb_Quaternion::Identity();

		// Euler: x = 90, y = 90, z = 45
		// 0.6532815f, 0.2705981f, 0.6532815f, 0.2705981f
		rlb_Quaternion q2 = rlb_Quaternion(rlb_Vector3(90, 90, 45));

		// Euler: x = -30, y = 60, z = -80
		rlb_Quaternion q3 = rlb_Quaternion(rlb_Vector3(-30, 60, -80));

		rlb_Quaternion q12 = q1 * q2;
		rlb_Quaternion q21 = q2 * q1;
		rlb_Quaternion q23 = q2 * q3;
		rlb_Quaternion q32 = q3 * q2;

		rlb_Vector4 expectedQ23 = rlb_Vector4(
			0.1391373f, 0.8899217f, -0.4339544f, -0.01906598f
		);

		rlb_Vector4 expectedQ32 = rlb_Vector4(
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

		rlb_Vector3 eulerRad = rlb_Vector3(2.96706f, 1.0472f, -1.5708f); // 170, 60, 90
		rlb_Vector3 eulerDeg = rlb_Vector3(45, 135, -35);

		rlb_Quaternion qRad = rlb_Quaternion(eulerRad, false);
		rlb_Quaternion qDeg = rlb_Quaternion(eulerDeg);

		rlb_Vector4 expectedQRad = rlb_Vector4(0.6408549f, -0.5792287f, -0.4055799f, -0.2988379f);
		rlb_Vector4 expectedQDeg = rlb_Vector4(0.3963371f, 0.770011f, -0.4435054f, 0.2308743f);

		int approxResult = Approx(qRad.GetComponents(), expectedQRad);
		AssertTest(approxResult == 1, "Quaternion Radians Euler To Components Error");
		
		approxResult = Approx(qDeg.GetComponents(), expectedQDeg);
		AssertTest(approxResult == 1, "Quaternion Degrees Euler To Components Error");

		return true;
	}

	
	bool QuaternionTest_FromAngleAxis(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion From Angle Axis");

		rlb_Quaternion q1NoAngle = rlb_Quaternion(0, rlb_Vector3(1, 0, 0));
		rlb_Quaternion q2NoAngle = rlb_Quaternion(0, rlb_Vector3(-.3f, .5f, .5f));
		rlb_Quaternion q3NoAngle = rlb_Quaternion(0, rlb_Vector3(0, 0, 0));

		rlb_Quaternion q1 = rlb_Quaternion(60, rlb_Vector3(1, 0, 0));
		rlb_Quaternion q2 = rlb_Quaternion(60, rlb_Vector3(-.3f, .5f, .5f));
		rlb_Quaternion q3 = rlb_Quaternion(60, rlb_Vector3(0, 0, 0));

		rlb_Quaternion q4 = rlb_Quaternion(160, rlb_Vector3(1, 1, -1));
		rlb_Quaternion q5 = rlb_Quaternion(270, rlb_Vector3(1, 1, -1));
		rlb_Quaternion q6 = rlb_Quaternion(273, rlb_Vector3(1, 1, -1));

		rlb_Quaternion q7 = rlb_Quaternion(-30, rlb_Vector3(1, 1, -1));
		rlb_Quaternion q8 = rlb_Quaternion(180, rlb_Vector3(1, 1, -1));
		rlb_Quaternion q9 = rlb_Quaternion(-350, rlb_Vector3(1, 1, -1));


		int approxResult = Approx(q1NoAngle.GetComponents(), rlb_Vector4(0, 0, 0, 1));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: No Angle 1");

		approxResult = Approx(q2NoAngle.GetComponents(), rlb_Vector4(0, 0, 0, 1));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: No Angle 2");

		approxResult = Approx(q3NoAngle.GetComponents(), rlb_Vector4(0, 0, 0, 1));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: No Angle 3");


		approxResult = Approx(q1.GetComponents(), rlb_Vector4(0.5f, 0, 0, 0.8660254f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q1");

		approxResult = Approx(q2.GetComponents(), rlb_Vector4(-0.1952834f, 0.3254723f, 0.3254723f, 0.8660254f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q2");

		approxResult = Approx(q3.GetComponents(), rlb_Vector4(0, 0, 0, 1));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q3");


		approxResult = Approx(q4.GetComponents(), rlb_Vector4(0.568579f, 0.568579f, -0.568579f, 0.1736482f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q4");

		approxResult = Approx(q5.GetComponents(), rlb_Vector4(0.4082483f, 0.4082483f, -0.4082483f, -0.7071068f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q5");

		approxResult = Approx(q6.GetComponents(), rlb_Vector4(0.3974217f, 0.3974217f, -0.3974217f, -0.7253744f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q6");


		approxResult = Approx(q7.GetComponents(), rlb_Vector4(-0.1494292f, -0.1494292f, 0.1494292f, 0.9659258f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q7");

		approxResult = Approx(q8.GetComponents(), rlb_Vector4(0.5773503f, 0.5773503f, -0.5773503f, 0.f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q8");

		approxResult = Approx(q9.GetComponents(), rlb_Vector4(-0.0503194f, -0.0503194f, 0.0503194f, -0.9961947f));
		AssertTest(approxResult == 1, "Angle Axis To Quaternion Error: q9");


		return true;
	}



	bool QuaternionTest_Inverse(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Inverse")

		rlb_Quaternion q1 = rlb_Quaternion(60, rlb_Vector3(1, 0, 0));
		rlb_Quaternion q2 = rlb_Quaternion(80, rlb_Vector3(-.3f, .5f, .5f));
		rlb_Quaternion q3 = rlb_Quaternion(135, rlb_Vector3(1, 0, -1));

		rlb_Quaternion q1Inverse = q1.GetInverse();
		rlb_Quaternion q2Inverse = q2.GetInverse();
		rlb_Quaternion q3Inverse = q3.GetInverse();

		rlb_Quaternion expectedQ1Inverse = rlb_Quaternion(-0.5f, 0, 0, 0.8660254f);
		rlb_Quaternion expectedQ2Inverse = rlb_Quaternion(0.2510515f, -0.4184191f, -0.4184191f, 0.7660444f);
		rlb_Quaternion expectedQ3Inverse = rlb_Quaternion(-0.6532815f, 0, 0.6532815f, 0.3826834f);

		int approxResult = Approx(q1Inverse.GetComponents(), expectedQ1Inverse.GetComponents());
		AssertTest(approxResult == 1, "Quaternion Inverse Error: q1");

		approxResult = Approx(q2Inverse.GetComponents(), expectedQ2Inverse.GetComponents());
		AssertTest(approxResult == 1, "Quaternion Inverse Error: q2");

		approxResult = Approx(q3Inverse.GetComponents(), expectedQ3Inverse.GetComponents());
		AssertTest(approxResult == 1, "Quaternion Inverse Error: q3");

		return true;
	}


	bool QuaternionTest_VectorRotation(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion Vector Rotation")

		rlb_Vector4 p0 = rlb_Vector4(1, 0, 0, 0);
		rlb_Vector4 p1 = rlb_Vector4(1, 1, 0, 0);
		rlb_Vector3 p2 = rlb_Vector3(100, 0, 0);
		rlb_Vector3 p3 = rlb_Vector3(100, 100, 100);
		rlb_Vector2 p4 = rlb_Vector2(-50, 0);
		

		// <1, 0, 0> 60 deg
		rlb_Quaternion q1 = rlb_Quaternion(0.5f, 0, 0, 0.8660254f);
		
		// <1, 1, 1> 45 deg
		rlb_Quaternion q2 = rlb_Quaternion(0.2209424, 0.2209424, 0.2209424, 0.9238795);

		// Check Hamiltonian works before anything else
		rlb_Quaternion hamQuat = rlb_Quaternion(0.0, 0.707, 0.0, .707);
		rlb_Vector4 hamResult = rlb_Quaternion::Hamiltonian(hamQuat.GetComponents(), p0);
		rlb_Vector4 expectedHam = rlb_Vector4(0.707106829, 0.0, -0.707106829, 0);

		rlb_Vector4 rotatedQ1P0 = q1 * p0;
		rlb_Vector4 rotatedQ1P1 = q1 * p1;
		rlb_Vector3 rotatedQ1P2 = q1 * p2;
		rlb_Vector3 rotatedQ1P3 = q1 * p3;
		rlb_Vector2 rotatedQ1P4 = q1 * p4;

		rlb_Vector4 rotatedQ2P0 = q2 * p0;
		rlb_Vector4 rotatedQ2P1 = q2 * p1;
		rlb_Vector3 rotatedQ2P2 = q2 * p2;
		rlb_Vector3 rotatedQ2P3 = q2 * p3;
		rlb_Vector2 rotatedQ2P4 = q2 * p4;

		rlb_Vector4 expectedRotatedQ1P0 = rlb_Vector4(1, 0, 0, 0);
		rlb_Vector4 expectedRotatedQ1P1 = rlb_Vector4(1, 0.5f, 0.8660254f, 0);
		rlb_Vector3 expectedRotatedQ1P2 = rlb_Vector3(100, 0, 0);
		rlb_Vector3 expectedRotatedQ1P3 = rlb_Vector3(100, -36.60254, 136.6025);
		rlb_Vector2 expectedRotatedQ1P4 = rlb_Vector2(-50, 0);

		rlb_Vector4 expectedRotatedQ2P0 = rlb_Vector4(0.8047378, 0.5058794, -0.3106172, 0);
		rlb_Vector4 expectedRotatedQ2P1 = rlb_Vector4(0.4941206, 1.310617, 0.1952622, 0);
		rlb_Vector3 expectedRotatedQ2P2 = rlb_Vector3(80.47379, 50.58794, -31.06172);
		rlb_Vector3 expectedRotatedQ2P3 = rlb_Vector3(100, 100, 100);
		rlb_Vector2 expectedRotatedQ2P4 = rlb_Vector2(-40.23689, -25.29397);

		int approxResult = Approx(hamResult, expectedHam);
		AssertTest(approxResult == 1, "Quaternion Hamiltonian Product Error");

		approxResult = Approx(rotatedQ1P0, expectedRotatedQ1P0);
		AssertTest(approxResult == 1, "Quaternion Rotation Error: q1 * p0");
		approxResult = Approx(rotatedQ1P1, expectedRotatedQ1P1);
		AssertTest(approxResult == 1, "Quaternion Rotation Error: q1 * p1");
		approxResult = Approx(rotatedQ1P2, expectedRotatedQ1P2);
		AssertTest(approxResult == 1, "Quaternion Rotation Error: q1 * p2");
		approxResult = Approx(rotatedQ1P3, expectedRotatedQ1P3);
		AssertTest(approxResult == 1, "Quaternion Rotation Error: q1 * p3");
		approxResult = Approx(rotatedQ1P4, expectedRotatedQ1P4);
		AssertTest(approxResult == 1, "Quaternion Rotation Error: q1 * p4");

		approxResult = Approx(rotatedQ2P0, expectedRotatedQ2P0);
		AssertTest(approxResult == 1, "Quaternion Rotation Error: q2 * p0");
		approxResult = Approx(rotatedQ2P1, expectedRotatedQ2P1);
		AssertTest(approxResult == 1, "Quaternion Rotation Error: q2 * p1");
		approxResult = Approx(rotatedQ2P2, expectedRotatedQ2P2);
		AssertTest(approxResult == 1, "Quaternion Rotation Error: q2 * p2");
		approxResult = Approx(rotatedQ2P3, expectedRotatedQ2P3);
		AssertTest(approxResult == 1, "Quaternion Rotation Error: q2 * p3");
		approxResult = Approx(rotatedQ2P4, expectedRotatedQ2P4);
		AssertTest(approxResult == 1, "Quaternion Rotation Error: q2 * p4");

		return true;
	}

	
	bool QuaternionTest_2D(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Quaternion 2D Functionality");

		rlb_Quaternion q1 = rlb_Quaternion::Quaternion2D(0);
		rlb_Quaternion q2 = rlb_Quaternion::Quaternion2D(60);
		rlb_Quaternion q3 = rlb_Quaternion::Quaternion2D(-135);

		rlb_Vector2 v1 = rlb_Vector2(50, 0);
		rlb_Vector2 v2 = rlb_Vector2(100, -75);

		rlb_Vector2 rotatedQ1V1 = q1 * v1;
		rlb_Vector2 rotatedQ2V1 = q2 * v1;
		rlb_Vector2 rotatedQ3V1 = q3 * v1;
		rlb_Vector2 v1AroundV2WithQ2 = q2.GetRotatedAroundPoint(v1, v2);

		rlb_Vector2 expectedQ1V1 = rlb_Vector2(50, 0);
		rlb_Vector2 expectedQ2V1 = rlb_Vector2(25, 43.301270189221932f);
		rlb_Vector2 expectedQ3V1 = rlb_Vector2(-35.355339059327376f, -35.355339059327376);
		rlb_Vector2 expectedV1AroundV2WithQ2 = rlb_Vector2(10.048094716167101, -80.801270189221932f);

		int approxResult = Approx(rotatedQ1V1, expectedQ1V1);
		AssertTest(approxResult == 1, "Quaternion 2D Rotation Error: q1 * v1");
		approxResult = Approx(rotatedQ2V1, expectedQ2V1);
		AssertTest(approxResult == 1, "Quaternion 2D Rotation Error: q2 * v1");
		approxResult = Approx(rotatedQ3V1, expectedQ3V1);
		AssertTest(approxResult == 1, "Quaternion 2D Rotation Error: q3 * v1");
		approxResult = Approx(v1AroundV2WithQ2, expectedV1AroundV2WithQ2);
		AssertTest(approxResult == 1, "Quaternion 2D Rotation Around Point Error: v1 around v2 using q2");

		return true;
	}
}