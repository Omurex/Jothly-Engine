#pragma once


namespace jothly
{
	class rlb_Color;
	struct rlb_Vector2;

	class ShapeDrawing2D
	{
	public:
		static void DrawCircle(int pixelX, int pixelY, float radius, rlb_Color color);
		static void DrawCircle(rlb_Vector2 pixelCoords, float radius, rlb_Color color);
	};
}