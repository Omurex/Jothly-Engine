#include "VectorTestSet.h"


namespace jothly
{
	int VectorTestSet::NormalizationTest()
	{
		int firstTestResult = v2a.GetNormalized() == Vector2(1, 0);
		PrintSingleResult(1, "Vec 2 Normal", firstTestResult, "", "");
	}


	void VectorTestSet::LoadTestFunctions()
	{
		
	}
}