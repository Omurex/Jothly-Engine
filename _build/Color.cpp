#include "Color.h"


namespace jothly
{
	const float Color::CHAR2FLOAT = 1.0f / 255.0f;
	const float Color::FLOAT2CHAR = 255.0f;


	unsigned char* Color::GetRGBA() const
	{
		unsigned char copy[4];
		copy[0] = GetR(); copy[1] = GetG(); copy[2] = GetB(); copy[3] = GetA();
		return copy;
	}


	float* Color::GetRGBAf() const
	{
		float copy[4];
		copy[0] = GetRf(); copy[1] = g; copy[2] = b; copy[3] = a;
		return copy;
	}


	Color Color::Lerp(const Color& first, const Color& second, float portion)
	{
		portion = std::clamp(portion, 0.0f, 1.0f);

		float* fRGBA = first.GetRGBAf();
		float* sRGBA = second.GetRGBAf();

		return Color(
			((sRGBA[0] - fRGBA[0]) * portion) + fRGBA[0],
			((sRGBA[1] - fRGBA[1]) * portion) + fRGBA[1],
			((sRGBA[2] - fRGBA[2]) * portion) + fRGBA[2],
			((sRGBA[3] - fRGBA[3]) * portion) + fRGBA[3]
		);
	}
}