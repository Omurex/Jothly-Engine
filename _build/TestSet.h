#pragma once

#include <utility>
#include <string>
#include <vector>


namespace jothly
{
	// Function that returns 1 if test successful, 0 if failed
	typedef int (*TestFunction)();

	class TestSet
	{
		protected:
		const float MOE = .001f; // Margin of Error

		std::vector<TestFunction> testFunctions;
		bool throwOnTestFail;


		TestSet(bool _throwOnTestFail) : throwOnTestFail(_throwOnTestFail) { LoadTestFunctions(); }

		virtual void LoadTestFunctions() = 0;
		std::pair<int, int> PerformTestCalls();

		void PrintSingleResult(int testNum, std::string shorthand, bool succeeded, std::string successMessage, std::string failMessage);
		void PrintCombinedResult(int numSucceeded, int numTotal);

		public:
		/// <returns>True if all tests succeeded, false if at least one failed</returns>
		bool RunTests()
		{
			#ifdef _DEBUG
			std::pair<int, int> results = PerformTestCalls();
			return results.first == results.second;
			#else
			return true;
			#endif
		}
	};
}

