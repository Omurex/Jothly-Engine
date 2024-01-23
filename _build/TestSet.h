#pragma once

#include <utility>
#include <string>
#include <vector>
#include <functional>


namespace jothly
{
	// Function that returns true if test successful, false if failed
	// out_shorthand is what the test will be titled when printing to the console
	// out_message is a message printed after the results of the test are printed
	typedef bool (*TestFunction)(std::string& out_shorthand, std::string& out_message);
	
	// Called from beginning of test functions to initialize variables and set up for AssertTest calls
	// NOTE: If calling this, there must be an out_message string variable in scope
	#define InitTest(sShorthand) out_shorthand = sShorthand; bool testResult = true;

	// Called from test functions after doing test check, will return from function with message if result is false
	// NOTE: If calling this, there must be an out_message string variable in scope
	#define AssertTest(bCheck, sFailMessage) if(bCheck == false) { out_message = sFailMessage; return false; }

	class TestSet
	{
		protected:

		std::vector<TestFunction> testFunctions;
		bool throwOnTestFail;


		TestSet(bool _throwOnTestFail) : throwOnTestFail(_throwOnTestFail) {}

		std::pair<int, int> PerformTestCalls();

		void PrintSingleResult(int testNum, std::string shorthand, bool succeeded, std::string message);
		void PrintCombinedResult(int numSucceeded, int numTotal);

		public:

		virtual void LoadTestFunctions() = 0;
		virtual std::string GetTitle() = 0;


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

