#include "Math.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
//#include "Color.h"

//#include <Eigen/Dense>


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
			if (Approx(val1[i], val2[i], marginOfError) == 0)
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


	/*Vector2 SolveSystemOfEquations(const Vector3 row1, const Vector3 row2)
	{
		Eigen::Matrix2f mat;
		mat << row1.x, row1.y, row2.x, row2.y;

		Eigen::Vector2f lastCol(row1.z, row2.z);
		Eigen::Vector2f result = mat.colPivHouseholderQr().solve(lastCol);

		return Vector2(result.x(), result.y());
	}*/
}