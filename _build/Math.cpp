#include "Math.hpp"


int Approx(float val1, float val2, float marginOfError)
{
	if (abs(val1 - val2) <= marginOfError) return 1;
	else return 0;
}
