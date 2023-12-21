#pragma once

#include <vector>
#include <assert.h>
#include "TestSet.h"


namespace jothly
{
	struct TestRunner
	{
		std::vector<TestSet*> testSets;

		TestRunner(bool preloadTestSets = true, bool throwErrorOnFail = true);
		~TestRunner() { for(int i = 0; i < testSets.size(); i++) delete testSets[i]; }

		void RunTests()
		{
			for (TestSet* test : testSets)
			{
				test->RunTests();
			}
		}

		template<typename T>
		void AddTestSet(bool throwErrorOnFail = false);

		private:
		/// <summary>
		/// Fill testSets with default test sets
		/// </summary>
		void PopulateTestSets(bool throwErrorOnFail);
	};


	template<typename T>
	inline void TestRunner::AddTestSet(bool throwErrorOnFail)
	{
		// Make sure passed in type is a test set
		bool isTestSet = std::is_base_of<TestSet, T>();
		assert(isTestSet);

		TestSet* testSet = static_cast<TestSet*>(new T(throwErrorOnFail));

		testSets.push_back(testSet);
	}
}