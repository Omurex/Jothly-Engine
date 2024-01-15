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


	bool QuaternionTest_Normalization(std::string& out_shorthand, std::string& out_message);
	bool QuaternionTest_QuaternionRotation(std::string& out_shorthand, std::string& out_message);
	bool QuaternionTest_Euler(std::string& out_shorthand, std::string& out_message);
	bool QuaternionTest_FromAngleAxis(std::string& out_shorthand, std::string& out_message);
	bool QuaternionTest_Inverse(std::string& out_shorthand, std::string& out_message);
	bool QuaternionTest_VectorRotation(std::string& out_shorthand, std::string& out_message);
	bool QuaternionTest_2D(std::string& out_shorthand, std::string& out_message);
}