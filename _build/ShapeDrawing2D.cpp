#include "ShapeDrawing2D.h"
#include "Color.h"
#include "Vector2.h"
#include "include/raylib.hpp"
#include "include/raylib-cpp-utils.hpp"
#include "include/raylib-cpp.hpp"


namespace jothly
{
	void ShapeDrawing2D::DrawCircle(int pixelX, int pixelY, float radius, Color color)
	{
		DrawCircle(Vector2((float) pixelX, (float) pixelY), radius, color);
	}


	void ShapeDrawing2D::DrawCircle(Vector2 pixelCoords, float radius, Color color)
	{
		((raylib::rlb_Vector2) pixelCoords).DrawCircle(radius, {color.GetR(), color.GetG(), color.GetB(), color.GetA()});
	}


    void ShapeDrawing2D::DrawLine(Vector2 start, Vector2 end, float thickness, Color color)
    {
		((raylib::rlb_Vector2) start).DrawLine(end, thickness, color);
    }


	void ShapeDrawing2D::DrawSquare(Vector2 topLeft, float sideLength, Color color, float rotationDeg)
	{
		((raylib::rlb_Vector2)topLeft).DrawRectangle(Vector2(sideLength, sideLength), color);
	}
}