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


	struct rlb_Vector2;
	struct rlb_Vector3;
	struct rlb_Vector4;
	class rlb_Color;


	/// <returns>1 if values are within margin of error of each other, 0 if not</returns>
	int Approx(float val1, float val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);

	// Will run approx function on each value of array
	int Approx(const float val1[], const float val2[], int len, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);

	// Specific approx implementations for structures and classes
	int Approx(const rlb_Vector2 val1, const rlb_Vector2 val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);
	int Approx(const rlb_Vector3 val1, const rlb_Vector3 val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);
	int Approx(const rlb_Vector4 val1, const rlb_Vector4 val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);
	int Approx(const rlb_Color val1, const rlb_Color val2, float marginOfError = MATH_DEFAULT_MARGIN_OF_ERROR);
}