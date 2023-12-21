#include "VectorTestSet.h"
#include "Math.hpp"
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

		AssertTest(vec2a.GetNormalized() == Vector2(1, 0), "Vec2 Normalize Error");
		AssertTest((Approx(vec2b.x, .707f) * Approx(vec2b.y, .707f)) == 1, "Vec2 Normalize Error");
		AssertTest((Approx(vec3.x, .577f) * Approx(vec3.y, .577f) * Approx(vec3.z, .577f)) == 1, "Vec3 Normalize Error");
		AssertTest(vec4 == Vector4(.5, .5, .5, .5), "Vec4 Normalize Error");
		
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