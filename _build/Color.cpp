#include "Color.h"


namespace jothly
{
	const float Color::CHAR2FLOAT = 1.0f / 255.0f;
	const float Color::FLOAT2CHAR = 255.0f;


	void Color::GetRGBA(unsigned char out_rgba[4]) const
	{
		out_rgba[0] = GetR(); out_rgba[1] = GetG(); out_rgba[2] = GetB(); out_rgba[3] = GetA();
	}


	void Color::GetRGBAf(float out_rgba[4]) const
	{
		out_rgba[0] = GetRf(); out_rgba[1] = GetGf(); out_rgba[2] = GetBf(); out_rgba[3] = GetAf();
	}


	bool Color::operator==(Color const& other)
	{
		return colorCode == other.colorCode;
	}


	Color Color::Lerp(const Color& first, const Color& second, float portion)
	{
		portion = std::clamp(portion, 0.0f, 1.0f);

		float fRGBA[4];
		float sRGBA[4];

		first.GetRGBAf(fRGBA);
		second.GetRGBAf(sRGBA);

		return Color(
			((sRGBA[0] - fRGBA[0]) * portion) + fRGBA[0],
			((sRGBA[1] - fRGBA[1]) * portion) + fRGBA[1],
			((sRGBA[2] - fRGBA[2]) * portion) + fRGBA[2],
			((sRGBA[3] - fRGBA[3]) * portion) + fRGBA[3]
		);
	}
}