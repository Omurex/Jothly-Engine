#include "Vector2i.h"
#include "Vector2.h"


namespace jothly
{
	float Vector2i::GetMagnitude()
	{
		return sqrtf((float) GetMagnitudeSquared());
	}


	int Vector2i::GetMagnitudeSquared()
	{
		return (x * x) + (y * y);
	}


	void Vector2i::Scale(int const& scale)
	{
		x *= scale; y *= scale;
	}


	Vector2 Vector2i::MultiplyComponents(const Vector2& other)
	{
		return Vector2(x * other.x, y * other.y);
	}


	Vector2i Vector2i::operator+(Vector2i const& other) const
	{
		return Vector2i(x + other.x, y + other.y);
	}


	Vector2 Vector2i::operator+(Vector2 const& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}


	Vector2i& Vector2i::operator+=(Vector2i const& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}


	Vector2i Vector2i::operator-(Vector2i const& other) const
	{
		return Vector2i(x - other.x, y - other.y);
	}


	Vector2 Vector2i::operator-(Vector2 const& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}


	Vector2i& Vector2i::operator-=(Vector2i const& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}


	Vector2 Vector2i::operator*(float const& scale) const
	{
		return Vector2(x * scale, y * scale);
	}


	Vector2 Vector2i::operator/(float const& scale) const
	{
		return Vector2(x / scale, y / scale);
	}


	bool Vector2i::operator==(Vector2i const& other)
	{
		return x == other.x && y == other.y;
	}


	Vector2i::operator Vector2() const
	{
		return Vector2((float) x, (float) y);
	}
}