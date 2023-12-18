#pragma once

#include <utility>


namespace jothly
{
	class UnitTest
	{
		// Returns num succeeded for first and total tests in second
		virtual std::pair<int, int> CallTestFunctions() = 0;

		public:
		// Returns num succeeded for first and total tests in second
		virtual std::pair<int, int> RunTests();
	};
}