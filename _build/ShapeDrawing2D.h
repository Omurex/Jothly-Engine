#pragma once


namespace jothly
{
	class Color;
	struct Vector2;

	class ShapeDrawing2D
	{
		public:
		static void DrawCircle(int pixelX, int pixelY, float radius, Color color);
		static void DrawCircle(Vector2 pixelCoords, float radius, Color color);

		static void DrawLine(Vector2 start, Vector2 end, float thickness, Color color);
	};
}