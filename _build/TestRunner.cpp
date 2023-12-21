#include "TestRunner.h"
#include "VectorTestSet.h"
#include "QuaternionTestSet.h"


namespace jothly
{
	TestRunner::TestRunner(bool preloadTestSets, bool throwErrorOnFail)
	{
		if (preloadTestSets)
		{
			PopulateTestSetsWithDefaults(throwErrorOnFail);
		}
	}


	void TestRunner::PopulateTestSetsWithDefaults(bool throwErrorOnFail)
	{
		AddTestSet<VectorTestSet>(true);
		AddTestSet<QuaternionTestSet>(true);
	}
}