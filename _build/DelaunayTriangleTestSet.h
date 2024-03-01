#pragma once

#include "TestSet.h"


namespace jothly
{
	class DelaunayTriangleTestSet : public TestSet
	{
	public:
		DelaunayTriangleTestSet(bool _throwOnTestFail) : TestSet(_throwOnTestFail) {}


		// Inherited via TestSet
		void LoadTestFunctions() override;

		// Inherited via TestSet
		std::string GetTitle() override;
	};


	bool DelaunayTriangleTestSet_Circumcircle(std::string& out_shorthand, std::string& out_message);
}