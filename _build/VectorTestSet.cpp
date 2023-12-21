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
	}


	bool VectorTest_Normalization(std::string& out_shorthand, std::string& out_message)
	{
		out_shorthand = "Vector Normalization";

		bool testsResult = true;

		Vector2 vec2a = Vector2(100, 0).GetNormalized();
		Vector2 vec2b = Vector2(100, 100).GetNormalized();
		Vector3 vec3 = Vector3(100, 100, 100).GetNormalized();
		Vector4 vec4 = Vector4(1, 1, 1, 1).GetNormalized();

		testsResult &= vec2a.GetNormalized() == Vector2(1, 0);
		if(testsResult == false) { out_message = "Vec2 Normalize Error"; return false; }

		testsResult &= (Approx(vec2b.x, .707f) * Approx(vec2b.y, .707f)) == 1;
		if (testsResult == false) { out_message = "Vec2 Normalize Error"; return false; }

		testsResult &= (Approx(vec3.x, .577f) * Approx(vec3.y, .577f) * Approx(vec3.z, .577f)) == 1;
		if (testsResult == false) { out_message = "Vec3 Normalize Error"; return false; }

		testsResult &= vec4 == Vector4(.5, .5, .5, .5);
		if (testsResult == false) { out_message = "Vec4 Normalize Error"; return false; }
		
		return testsResult;
	}
}