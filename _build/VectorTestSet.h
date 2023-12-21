#pragma once

#include "TestSet.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


namespace jothly
{
	class VectorTestSet : public TestSet
	{
		Vector2 v2a = Vector2(100, 0);
		Vector2 v2b = Vector2(150, 150);
		Vector3 v3a = Vector3(-25, -100);
		Vector4 v4a = Vector4(1, 2, 3, 4);


		// Test Functions
		int NormalizationTest();


		public:
		VectorTestSet(bool _throwOnTestFail) : TestSet(_throwOnTestFail) {}

		// Inherited via TestSet
		void LoadTestFunctions() override;
	};
}