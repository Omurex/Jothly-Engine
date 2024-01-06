#include "VectorTestSet.h"
#include "Math.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


namespace jothly
{
	void VectorTestSet::LoadTestFunctions()
	{
		testFunctions.push_back(VectorTest_Normalization);
		testFunctions.push_back(VectorTest_UnionComponents);
		testFunctions.push_back(VectorTest_Arithmetic);
	}


	std::string VectorTestSet::GetTitle()
	{
		return "VECTOR TESTS";
	}


	bool VectorTest_Normalization(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Vector Normalization");

		Vector2 vec2a = Vector2(100, 0).GetNormalized();
		Vector2 vec2b = Vector2(100, 100).GetNormalized();
		Vector3 vec3 = Vector3(100, 100, 100).GetNormalized();
		Vector4 vec4 = Vector4(1, 1, 1, 1).GetNormalized();
		Vector2 vec20 = Vector2(0).GetNormalized();
		Vector3 vec30 = Vector3(0).GetNormalized();
		Vector4 vec40 = Vector4(0).GetNormalized();

		Vector2 expectedVec2a = Vector2(1, 0);
		Vector2 expectedVec2b = Vector2(0.70710678118f);
		Vector3 expectedVec3 = Vector3(0.57735026919f);
		Vector4 expectedVec4 = Vector4(.5);
		Vector2 expectedVec20 = Vector2(0);
		Vector3 expectedVec30 = Vector3(0);
		Vector4 expectedVec40 = Vector4(0);

		AssertTest(vec2a.GetNormalized() == expectedVec2a, "Vec2 Normalize Error 1");
		AssertTest(Approx(vec2b, expectedVec2b) == 1, "Vec2 Normalize Error 2");
		AssertTest(Approx(vec3, expectedVec3) == 1, "Vec3 Normalize Error");
		AssertTest(Approx(vec4, expectedVec4) == 1, "Vec4 Normalize Error");
		AssertTest(Approx(vec20, expectedVec20) == 1, "Vec4 <0, 0> Normalize Error");
		AssertTest(Approx(vec30, expectedVec30) == 1, "Vec3 <0, 0, 0> Normalize Error");
		AssertTest(Approx(vec40, expectedVec40) == 1, "Vec4 <0, 0, 0, 0> Normalize Error");
		
		return testResult;
	}


	bool VectorTest_UnionComponents(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Vector Normalization");

		Vector2 vec2 = Vector2(1, 2);
		Vector3 vec3 = Vector3(1, 2, 3);
		Vector4 vec4 = Vector4(1, 2, 3, 4);

		vec2.components[1] = 9;
		vec3.components[2] = 9;
		vec4.components[3] = 9;

		AssertTest(vec2.y == 9, "Vec2 Union Components Error");
		AssertTest(vec3.z == 9, "Vec3 Union Components Error");
		AssertTest(vec4.w == 9, "Vec4 Union Components Error");

		return true;
	}


	bool VectorTest_Arithmetic(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Vector Arithmetic");

		{
			AssertTest((Vector2(1, 3) + Vector2(4, 4)) == Vector2(5, 7), "Vec2 Addition Error");
			AssertTest((Vector2(5, 7) - Vector2(4, 4)) == Vector2(1, 3), "Vec2 Subtraction Error");

			Vector2 vec2 = Vector2(3, 5) * 3;
			AssertTest((Approx(vec2.x, 9) * Approx(vec2.y, 15)), "Vec2 Multiplication Error");

			vec2 = vec2 / 3;
			AssertTest((Approx(vec2.x, 3) * Approx(vec2.y, 5)), "Vec2 Division Error");
		}

		{
			AssertTest((Vector3(1, 3, 5) + Vector3(4, 4, 4)) == Vector3(5, 7, 9), "Vec3 Addition Error");
			AssertTest((Vector3(5, 7, 9) - Vector3(4, 4, 4)) == Vector3(1, 3, 5), "Vec3 Subtraction Error");

			Vector3 vec3 = Vector3(3, 5, 3) * 3;
			AssertTest((Approx(vec3.x, 9) * Approx(vec3.y, 15) * Approx(vec3.z, 9)), "Vec3 Multiplication Error");

			vec3 = vec3 / 3;
			AssertTest((Approx(vec3.x, 3) * Approx(vec3.y, 5) * Approx(vec3.z, 3)), "Vec3 Division Error");
		}

		{
			AssertTest((Vector4(1, 3, 5, 7) + Vector4(4, 4, 4, 4)) == Vector4(5, 7, 9, 11), "Vec4 Addition Error");
			AssertTest((Vector4(5, 7, 9, 11) - Vector4(4, 4, 4, 4)) == Vector4(1, 3, 5, 7), "Vec4 Subtraction Error");

			Vector4 vec4 = Vector4(3, 5, 3, 5) * 3;
			AssertTest((Approx(vec4.x, 9) * Approx(vec4.y, 15) * Approx(vec4.z, 9) * Approx(vec4.w, 15)), 
				"Vec4 Multiplication Error");

			vec4 = vec4 / 3;
			AssertTest((Approx(vec4.x, 3) * Approx(vec4.y, 5) * Approx(vec4.z, 3) * Approx(vec4.w, 5)), "Vec4 Division Error");
		}

		return true;
	}
}