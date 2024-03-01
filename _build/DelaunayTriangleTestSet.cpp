#include "DelaunayTriangleTestSet.h"
#include "DelaunayTriangle.h"


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

		DelaunayTriangle

		return true;
	}
}