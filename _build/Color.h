#pragma once

#include <algorithm>


//namespace raylib
//{
//	class Color;
//}


namespace jothly
{
	class rlb_Color
	{
		static const float CHAR2FLOAT;
		static const float FLOAT2CHAR;


		union // https://www.reddit.com/r/GraphicsProgramming/comments/11m85f1/floats_vs_unsigned_ints_for_representing_colors/
		{
			struct 
			{
				unsigned char r;
				unsigned char g;
				unsigned char b;
				unsigned char a;
			};

			unsigned char rgba[4];

			uint32_t colorCode; // Use to instantly set color
		};

		
		static float CharToFloat(unsigned char c) { return c * CHAR2FLOAT; }
		static unsigned char FloatToChar(float f) { return f * FLOAT2CHAR; }


		public:

		/*static const Color WHITE;
		static const Color BLACK;
		static const Color GREY;
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color YELLOW;
		static const Color ORANGE;
		static const Color PURPLE;
		static const Color MAGENTA;
		static const Color PINK;
		static const Color CYAN;*/

		rlb_Color() : colorCode(0xFFFFFFFF) {}
		rlb_Color(const rlb_Color& col) : colorCode(col.colorCode) {}

		// Don't use setters since we know rlb_Color values are unsigned chars -- clamped between 0 and 255
		//Color(const raylib::Color& col);

		rlb_Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a = 255) : r(_r), g(_g), b(_b), a(_a) {}
		rlb_Color(unsigned char _rgba[4]) : r(_rgba[0]), g(_rgba[1]), b(_rgba[2]), a(_rgba[3]) {}

		rlb_Color(int _r, int _g, int _b, int _a = 255) { SetR(_r); SetG(_g); SetB(_b); SetA(_a); }
		rlb_Color(int _rgba[]) { SetR(_rgba[0]); SetG(_rgba[1]); SetB(_rgba[2]); SetA(_rgba[3]); }

		rlb_Color(float _r, float _g, float _b, float _a = 1.0f) { SetRf(_r); SetGf(_g); SetBf(_b); SetAf(_a); }
		rlb_Color(float _rgba[]) { SetRf(_rgba[0]); SetGf(_rgba[1]); SetBf(_rgba[2]); SetAf(_rgba[3]); }

		rlb_Color(uint32_t _colorCode) : colorCode(_colorCode) {}


		unsigned char GetR() const { return r; }
		unsigned char GetG() const { return g; }
		unsigned char GetB() const { return b; }
		unsigned char GetA() const { return a; }
		void GetRGBA(unsigned char out_rgba[4]) const;

		float GetRf() const { return CharToFloat(r); }
		float GetGf() const { return CharToFloat(g); }
		float GetBf() const { return CharToFloat(b); }
		float GetAf() const { return CharToFloat(a); }
		void GetRGBAf(float out_rgba[4]) const;

		uint32_t GetColorCode() { return colorCode; }

		void SetR(int _r) { r = std::clamp(_r, 0, 255); }
		void SetG(int _g) { g = std::clamp(_g, 0, 255); }
		void SetB(int _b) { b = std::clamp(_b, 0, 255); }
		void SetA(int _a) { a = std::clamp(_a, 0, 255); }
		void SetRGBA(int _rgba[4]) { SetR(_rgba[0]); SetG(_rgba[1]); SetB(_rgba[2]); SetA(_rgba[3]); }

		void SetRf(float _r) { SetR(FloatToChar(_r)); }
		void SetGf(float _g) { SetG(FloatToChar(_g)); }
		void SetBf(float _b) { SetB(FloatToChar(_b)); }
		void SetAf(float _a) { SetA(FloatToChar(_a)); }
		void SetRGBAf(float _rgba[4]) { SetRf(_rgba[0]); SetGf(_rgba[1]); SetBf(_rgba[2]); SetAf(_rgba[3]); }

		void SetColorCode(uint32_t _colorCode) { colorCode = _colorCode; }


		bool operator==(rlb_Color const& other);

		//operator raylib::Color() const;


		static rlb_Color Lerp(const rlb_Color& first, const rlb_Color& second, float portion);
	};
}

