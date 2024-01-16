#include "ShapeDrawing2D.h"
#include "raylib.h"
#include "Color.h"
#include "Vector2.h"


namespace jothly
{
	void ShapeDrawing2D::DrawCircle(int pixelX, int pixelY, float radius, Color color)
	{
		DrawCircle(Vector2(pixelX, pixelY), radius, color);
	}


	void ShapeDrawing2D::DrawCircle(Vector2 pixelCoords, float radius, Color color)
	{
		DrawCircleV(pixelCoords, radius, color);
	}
}