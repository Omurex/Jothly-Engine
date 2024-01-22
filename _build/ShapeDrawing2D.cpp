#include "ShapeDrawing2D.h"
#include "Color.h"
#include "Vector2.h"
#include "include/raylib.hpp"
#include "include/raylib-cpp-utils.hpp"
#include "include/raylib-cpp.hpp"


namespace jothly
{
	void ShapeDrawing2D::DrawCircle(int pixelX, int pixelY, float radius, rlb_Color color)
	{
		DrawCircle(rlb_Vector2(pixelX, pixelY), radius, color);
	}


	void ShapeDrawing2D::DrawCircle(rlb_Vector2 pixelCoords, float radius, rlb_Color color)
	{
		((raylib::rlb_Vector2) pixelCoords).DrawCircle(radius, {color.GetR(), color.GetG(), color.GetB(), color.GetA()});
	}
}