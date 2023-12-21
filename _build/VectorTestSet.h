#pragma once

#include "TestSet.h"


namespace jothly
{
	class VectorTestSet : public TestSet
	{
		public:
		VectorTestSet(bool _throwOnTestFail) : TestSet(_throwOnTestFail) {}

		void LoadTestFunctions() override;

		std::string GetTitle() override;
	};


	bool VectorTest_Normalization(std::string& out_shorthand, std::string& out_message);
	bool VectorTest_UnionComponents(std::string& out_shorthand, std::string& out_message);
	bool VectorTest_Arithmetic(std::string& out_shorthand, std::string& out_message);
}