#include "Color.h"



namespace jothly
{
	const float rlb_Color::CHAR2FLOAT = 1.0f / 255.0f;
	const float rlb_Color::FLOAT2CHAR = 255.0f;

	/*const Color Color::WHITE = Color(255, 255, 255);
	const Color Color::BLACK = Color(0, 0, 0);
	const Color Color::GREY = Color(.5f, .5f, .5f);
	const Color Color::RED = Color(255, 0, 0);
	const Color Color::GREEN = Color(0, 255, 0);
	const Color Color::BLUE = Color(0, 0, 255);
	const Color Color::YELLOW = Color(255, 255, 0);
	const Color Color::ORANGE = Color(255, 196, 0);
	const Color Color::PURPLE = Color(123, 0, 255);
	const Color Color::MAGENTA = Color(200, 0, 255);
	const Color Color::PINK = Color(255, 0, 255);
	const Color Color::CYAN = Color(0, 213, 255);*/
}


//#include "include/Color.hpp"


namespace jothly
{
	void rlb_Color::GetRGBA(unsigned char out_rgba[4]) const
	{
		out_rgba[0] = GetR(); out_rgba[1] = GetG(); out_rgba[2] = GetB(); out_rgba[3] = GetA();
	}


	void rlb_Color::GetRGBAf(float out_rgba[4]) const
	{
		out_rgba[0] = GetRf(); out_rgba[1] = GetGf(); out_rgba[2] = GetBf(); out_rgba[3] = GetAf();
	}


	bool rlb_Color::operator==(rlb_Color const& other)
	{
		return colorCode == other.colorCode;
	}

	/*Color::operator raylib::Color() const
	{
		return { r, g, b, a };
	}*/
}


jothly::rlb_Color jothly::rlb_Color::Lerp(const rlb_Color& first, const rlb_Color& second, float portion)
{
	portion = std::clamp(portion, 0.0f, 1.0f);

	float fRGBA[4];
	float sRGBA[4];

	first.GetRGBAf(fRGBA);
	second.GetRGBAf(sRGBA);

	return rlb_Color(
		((sRGBA[0] - fRGBA[0]) * portion) + fRGBA[0],
		((sRGBA[1] - fRGBA[1]) * portion) + fRGBA[1],
		((sRGBA[2] - fRGBA[2]) * portion) + fRGBA[2],
		((sRGBA[3] - fRGBA[3]) * portion) + fRGBA[3]
	);
}