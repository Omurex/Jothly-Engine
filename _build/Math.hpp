#pragma once

#include <cmath>


/// <returns>1 if values are within margin of error of each other, 0 if not</returns>
int Approx(float val1, float val2, float marginOfError = .01f);