#pragma once

#include <cmath>

// Degree to radians
#define D2R 0.01745329251f

// Radians to degrees
#define R2D 57.2957795131f

#define PI 3.14159265358979323846f

#define MATH_DEFAULT_MARGIN_OF_ERROR .0001f


namespace jothly
{
	struct Vector2;
	struct Vector3;
	struct Vector4;


	/// <returns>1 if values are within margin of error of each other, 0 if not</returns>
	int Approx(float val1, float val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);

	// Will run approx function on each value of array
	int Approx(const float val1[], const float val2[], int len, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);

	int Approx(const Vector2 val1, const Vector2 val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);

	int Approx(const Vector3 val1, const Vector3 val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);

	int Approx(const Vector4 val1, const Vector4 val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);
}