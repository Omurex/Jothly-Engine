#include "TestSet.h"
#include <iostream>
#include <stdexcept>


using namespace std;


namespace jothly
{
	std::pair<int, int> TestSet::PerformTestCalls()
	{
		int numSucceeded = 0;
		int numTotal = 0;

		int secondTestResult = v3a.x == v3a.components[0];
		PrintSingleResult(2, "X == Component", secondTestResult, "", "");
		numSucceeded += secondTestResult;
		numTotal++;

		return std::pair<int, int>();
	}

	
	void TestSet::PrintSingleResult(int testNum, std::string shorthand, bool succeeded, std::string successMessage, std::string failMessage)
	{
		std::string print = "TEST #" + to_string(testNum) + " - " + shorthand + "\n";

		if (succeeded)
		{
			print += "SUCCEEDED";

			if (successMessage == "")
			{
				print += "\n";
			}
			else
			{
				print += " - " + successMessage + "\n";
			}
		}
		else
		{
			print += "FAILED\n";

			if (successMessage == "")
			{
				print += "\n";
			}
			else
			{
				print += " - " + failMessage + "\n";
			}

			if (throwOnTestFail)
			{
				throw runtime_error(print);
			}
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