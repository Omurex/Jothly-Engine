#pragma once

#include "include/Vector3.hpp"
#include "include/Vector4.hpp"


namespace jothly
{
	struct rlb_Vector3;


	struct rlb_Vector4
	{
		union
		{
			struct 
			{
				float x;
				float y;
				float z;
				float w; 
			};

			float components[4];
		};


		rlb_Vector4() : x(0), y(0), z(0), w(0) {}
		rlb_Vector4(float val) : x(val), y(val), z(val), w(val) {}
		rlb_Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
		rlb_Vector4(const rlb_Vector4& vec4) : rlb_Vector4(vec4.x, vec4.y, vec4.z, vec4.w) {}
		rlb_Vector4(const rlb_Vector3& vec3);

		void Normalize();
		void Normalize(float precomputedMagnitudeSquared);
		rlb_Vector4 GetNormalized();
		rlb_Vector4 GetNormalized(float precomputedMagnitudeSquared);
		float GetMagnitude();
		float GetMagnitudeSquared();

		void Scale(float const& scale);

		rlb_Vector4 operator+(rlb_Vector4 const& other);
		rlb_Vector4 operator-(rlb_Vector4 const& other);
		rlb_Vector4 operator*(float const& scale);
		rlb_Vector4 operator/(float const& scale);
		bool operator==(rlb_Vector4 const& other);

		operator rlb_Vector3() const;
		//operator const float*() const;

		// Convert to RayLib version
		operator raylib::rlb_Vector3() const { return { x, y, z }; };
		operator raylib::rlb_Vector4() const { return { x, y, z, w }; };
	};
}