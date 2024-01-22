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
		DrawCircle(Vector2(pixelX, pixelY), radius, color);
	}


	void ShapeDrawing2D::DrawCircle(Vector2 pixelCoords, float radius, Color color)
	{
		((raylib::Vector2) pixelCoords).DrawCircle(radius, color);
	}
}