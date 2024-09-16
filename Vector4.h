#pragma once


namespace jothly
{
	struct Vector3;


	struct Vector4
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


		Vector4() : x(0), y(0), z(0), w(0) {}
		Vector4(float val) : x(val), y(val), z(val), w(val) {}
		Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
		Vector4(const Vector4& vec4) : Vector4(vec4.x, vec4.y, vec4.z, vec4.w) {}
		Vector4(const Vector3& vec3);

		void Normalize();
		void Normalize(float precomputedMagnitudeSquared);
		Vector4 GetNormalized();
		Vector4 GetNormalized(float precomputedMagnitudeSquared);
		float GetMagnitude();
		float GetMagnitudeSquared();

		void Scale(float const& scale);

		Vector4 operator+(Vector4 const& other);
		Vector4 operator-(Vector4 const& other);
		Vector4 operator*(float const& scale);
		Vector4 operator/(float const& scale);
		bool operator==(Vector4 const& other);

		operator Vector3() const;
	};
}