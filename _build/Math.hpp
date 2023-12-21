#pragma once

#include <math.h>


/// <returns>1 if values are within margin of error of each other, 0 if not</returns>
int Approx(float val1, float val2, float marginOfError = .01f)
{
	if(abs(val1 - val2) <= marginOfError) return 1;
	else return 0;
}