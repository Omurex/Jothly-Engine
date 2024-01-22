#pragma once

#include "include/Vector2.hpp"
#include "include/Vector3.hpp"


namespace jothly
{
	struct rlb_Vector3;
	
	
	struct rlb_Vector2
	{
		union
		{
			struct
			{
				float x;
				float y;
			};

			float components[2];
		};


		rlb_Vector2() : x(0), y(0) {}
		rlb_Vector2(float val) : x(val), y(val) {}
		rlb_Vector2(float _x, float _y) : x(_x), y(_y) {}
		rlb_Vector2(const rlb_Vector2& vec2) : rlb_Vector2(vec2.x, vec2.y) {}
		rlb_Vector2(const rlb_Vector3& vec3);

		void Normalize();
		void Normalize(float precomputedMagnitudeSquared);
		rlb_Vector2 GetNormalized();
		rlb_Vector2 GetNormalized(float precomputedMagnitudeSquared);
		float GetMagnitude();
		float GetMagnitudeSquared();

		void Scale(float const& scale);
	
		rlb_Vector2 operator+(rlb_Vector2 const& other);
		rlb_Vector3 operator+(rlb_Vector3 const& other);
		rlb_Vector2& operator+=(rlb_Vector2 const& other);
		rlb_Vector2& operator+=(rlb_Vector3 const& other);
		rlb_Vector2 operator-(rlb_Vector2 const& other);
		rlb_Vector3 operator-(rlb_Vector3 const& other);
		rlb_Vector2& operator-=(rlb_Vector2 const& other);
		rlb_Vector2& operator-=(rlb_Vector3 const& other);
		rlb_Vector2 operator*(float const& scale);
		rlb_Vector2 operator/(float const& scale);
		bool operator==(rlb_Vector2 const& other);

		operator rlb_Vector3() const;

		// Convert to RayLib version
		operator raylib::rlb_Vector2() { return {x, y}; };
		operator raylib::rlb_Vector3() { return {x, y, 0}; }
	};
}