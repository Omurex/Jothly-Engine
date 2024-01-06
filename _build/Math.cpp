#include "Math.h"
#include <raymath.h>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


namespace jothly
{
	int Approx(float val1, float val2, float marginOfError)
	{
		if (abs(val1 - val2) <= marginOfError) return 1;
		else return 0;
	}


	int Approx(const float val1[], const float val2[], int len, float marginOfError)
	{
		for (int i = 0; i < len; i++)
		{
			if(Approx(val1[i], val2[i], marginOfError) == 0) 
				return 0;
		}

		return 1;
	}


	int Approx(const Vector2 val1, const Vector2 val2, float marginOfError)
	{
		return Approx(val1.components, val2.components, 2, marginOfError);
	}

	
	int Approx(const Vector3 val1, const Vector3 val2, float marginOfError)
	{
		return Approx(val1.components, val2.components, 3, marginOfError);
	}


	int Approx(const Vector4 val1, const Vector4 val2, float marginOfError)
	{
		return Approx(val1.components, val2.components, 4, marginOfError);
	}
}