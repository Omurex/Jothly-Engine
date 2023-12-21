#include "TestRunner.h"
#include "VectorTestSet.h"


namespace jothly
{
	TestRunner::TestRunner(bool preloadTestSets, bool throwErrorOnFail)
	{
		if (preloadTestSets)
		{
			PopulateTestSets(throwErrorOnFail);
		}
	}


	void TestRunner::PopulateTestSets(bool throwErrorOnFail)
	{
		AddTestSet<VectorTestSet>(true);
	}
}