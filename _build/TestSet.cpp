#include "TestSet.h"
#include <iostream>
#include <stdexcept>
#include <assert.h>


using namespace std;


namespace jothly
{
	std::pair<int, int> TestSet::PerformTestCalls()
	{
		int numSucceeded = 0;
		int numTotal = 0;

		std::cout << "\n\n" << GetTitle() << std::endl;
		std::cout << "-----------------------------------------" << std::endl;

		for (int i = 0; i < testFunctions.size(); i++)
		{
			TestFunction test = testFunctions[i];

			std::string shortHand;
			std::string message;
			bool success = test(shortHand, message);

			numSucceeded += success ? 1 : 0;
			numTotal++;

			PrintSingleResult(i, shortHand, success, message);
		}

		PrintCombinedResult(numSucceeded, numTotal);

		return std::pair<int, int>(numSucceeded, numTotal);
	}

	
	void TestSet::PrintSingleResult(int testNum, std::string shorthand, bool succeeded, std::string message)
	{
		assert(shorthand != ""); // Shorthand should always describe the test

		std::string print = "TEST #" + to_string(testNum) + " - " + shorthand + "\n";

		if (succeeded)
		{
			print += "SUCCEEDED";
		}
		else
		{
			print += "FAILED\n";
		}

		if (message == "")
		{
			print += "\n";
		}
		else
		{
			print += " - " + message + "\n";
		}

		if (!succeeded && throwOnTestFail) // Failed and should throw
		{
			throw runtime_error(print);
		}

		print += "\n";

		std::cout << print << std::endl;
	}


	void TestSet::PrintCombinedResult(int numSucceeded, int numTotal)
	{
		std::string print = "TESTS RAN: " + to_string(numTotal) + "\n";
		print += "SUCCEEDED: " + to_string(numSucceeded) + "\n";
		print += "FAILED: " + to_string(numTotal - numSucceeded) + "\n";

		std::cout << print << std::endl;
	}
}