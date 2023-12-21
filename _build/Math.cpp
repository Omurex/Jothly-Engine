#include "Math.hpp"


int Approx(float val1, float val2, float marginOfError)
{
	if (abs(val1 - val2) <= marginOfError) return 1;
	else return 0;
}


int Approx(const float val1[], const float val2[], float len, float marginOfError)
{
	for (int i = 0; i < len; i++)
	{
		if(Approx(val1[i], val2[i], marginOfError) == 0) 
			return 0;
	}

	return 1;
}
