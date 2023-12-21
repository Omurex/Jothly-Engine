#pragma once

#include <cmath>


/// <returns>1 if values are within margin of error of each other, 0 if not</returns>
int Approx(float val1, float val2, float marginOfError = .01f);

// Will run approx function on each value of array
int Approx(const float val1[], const float val2[], float len, float marginOfError = .01f);