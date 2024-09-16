#pragma once

#include <cmath>


namespace jothly
{
	// Degree to radians
	#define DEG2RAD 0.01745329251f

	// Radians to degrees
	#define RAD2DEG 57.2957795131f

	#define PI 3.14159265358979323846f

	#define MATH_DEFAULT_MARGIN_OF_ERROR .0001f


	struct Vector2;
	struct Vector3;
	struct Vector4;


	/// <returns>1 if values are within margin of error of each other, 0 if not</returns>
	int Approx(float val1, float val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);

	// Will run approx function on each value of array
	int Approx(const float val1[], const float val2[], int len, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);

	// Specific approx implementations for structures and classes
	int Approx(const Vector2 val1, const Vector2 val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);
	int Approx(const Vector3 val1, const Vector3 val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);
	int Approx(const Vector4 val1, const Vector4 val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);

	Vector2 SolveSystemOfEquations(const Vector3 row1, const Vector3 row2);
}