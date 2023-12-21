#pragma once

#include "TestSet.h"


namespace jothly
{
	class VectorTestSet : public TestSet
	{
		public:
		VectorTestSet(bool _throwOnTestFail) : TestSet(_throwOnTestFail) {}

		// Inherited via TestSet
		void LoadTestFunctions() override;
	};


	bool VectorTest_Normalization(std::string& out_shorthand, std::string& out_message);
}