#pragma once

#include "TestSet.h"


namespace jothly
{
	class QuaternionTestSet : public TestSet
	{
		public:
		QuaternionTestSet(bool _throwOnTestFail) : TestSet(_throwOnTestFail) {}


		// Inherited via TestSet
		void LoadTestFunctions() override;

		// Inherited via TestSet
		std::string GetTitle() override;
	};


	bool QuaternionTest_CoreFunctionality(std::string& out_shorthand, std::string& out_message);
}