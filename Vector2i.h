#pragma once

#include <string>


namespace jothly
{

	struct Vector2;


	struct Vector2i
	{
		union
		{
			struct
			{
				int x;
				int y;
			};

			int components[2];
		};

		Vector2i() : x(0), y(0) {}
		Vector2i(int val) : x(val), y(val) {}
		Vector2i(int _x, int _y) : x(_x), y(_y) {}

		float GetMagnitude();
		int GetMagnitudeSquared();

		void Scale(int const& scale);
		Vector2 MultiplyComponents(const Vector2& other);
		Vector2i MultiplyComponents(const Vector2i& other) { return Vector2i(x * other.x, y * other.y); }

		std::string ToString() { return "<" + std::to_string(x) + " , " + std::to_string(y) + ">"; }

		Vector2i operator+(Vector2i const& other) const;
		Vector2 operator+(Vector2 const& other) const;
		Vector2i& operator+=(Vector2i const& other);
		Vector2i operator-(Vector2i const& other) const;
		Vector2 operator-(Vector2 const& other) const;
		Vector2i& operator-=(Vector2i const& other);
		Vector2 operator*(float const& scale) const;
		Vector2 operator/(float const& scale) const;
		bool operator==(Vector2i const& other);
	};
}