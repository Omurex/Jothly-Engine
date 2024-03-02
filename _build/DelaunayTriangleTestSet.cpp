#include "DelaunayTriangleTestSet.h"
#include "DelaunayTriangle.h"
#include "Math.h"


namespace jothly
{
	void DelaunayTriangleTestSet::LoadTestFunctions()
	{
		testFunctions.push_back(DelaunayTriangleTestSet_Circumcircle);
	}


	std::string DelaunayTriangleTestSet::GetTitle()
	{
		return "DELAUNAY TRIANGLE TESTS";
	}


	bool DelaunayTriangleTestSet_Circumcircle(std::string& out_shorthand, std::string& out_message)
	{
		InitTest("Delaunay Triangle Circumcircle Test");

		DelaunayTriangle tri = DelaunayTriangle(Vector2(100, 100), Vector2(200, 100), Vector2(75, 300));

		float calculatedCircumradius = tri.GetCircumradius();
		float expectedCircumradius = 118.84248043629391f;

		AssertTest(Approx(calculatedCircumradius, expectedCircumradius), "Delaunay Triangle Circumradius Calculation Error");

		return true;
	}
}