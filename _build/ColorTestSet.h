#pragma once

#include "TestSet.h"


namespace jothly
{
	class ColorTestSet : public TestSet
	{
		public:
		ColorTestSet(bool _throwOnTestFail) : TestSet(_throwOnTestFail) {}


		// Inherited via TestSet
		void LoadTestFunctions() override;

		// Inherited via TestSet
		std::string GetTitle() override;
	};


	bool ColorTest_Construction(std::string& out_shorthand, std::string& out_message);
	bool ColorTest_Operations(std::string& out_shorthand, std::string& out_message);
}