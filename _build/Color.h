#pragma once

#include <algorithm>

namespace jothly
{
	class Color
	{
		const float CHAR2FLOAT = 1.0f / 255.0f;
		const float FLOAT2CHAR = 255.0f;


		union // https://www.reddit.com/r/GraphicsProgramming/comments/11m85f1/floats_vs_unsigned_ints_for_representing_colors/
		{
			struct 
			{
				char r;
				char g;
				char b;
				char a;
			};

			char rgba[4];

			uint32_t colorCode; // Use to instantly set color
		};

		
		float CharToFloat(char c) { return c * CHAR2FLOAT; }
		char FloatToChar(float f) { return f * FLOAT2CHAR; }



		public:

		Color();
		Color(const Color& col);
		Color(int _r, int _g, int _b, int _a = 255);
		Color(int _rgba[]);
		Color(float _r, float _g, float _b, float _a = 1);
		Color(float _rgba[]);
		Color(uint32_t _colorCode);

		char GetR() { return r; }
		char GetG() { return g; }
		char GetB() { return b; }
		char GetA() { return a; }
		const char* GetRGBA() { return rgba; }

		float GetRf() { return CharToFloat(r); }
		float GetGf() { return CharToFloat(g); }
		float GetBf() { return CharToFloat(b); }
		float GetAf() { return CharToFloat(a); }
		const float* GetRGBAf();

		uint32_t GetColorCode() { return colorCode; }

		void SetR(char _r) { r = std::clamp(_r, 0, 255); }
		void SetG(char _g) { g = std::clamp(_g, 0, 255); }
		void SetB(char _b) { b = std::clamp(_b, 0, 255); }
		void SetA(char _a) { a = std::clamp(_a, 0, 255); }
		void SetRGBA(char _rgba[4]) { SetR(_rgba[0]); SetG(_rgba[1]); SetB(_rgba[2]); SetA(_rgba[3]); }

		void SetRf(float _r) { SetR(FloatToChar(_r)); }
		void SetGf(float _g) { SetG(FloatToChar(_g)); }
		void SetBf(float _b) { SetB(FloatToChar(_b)); }
		void SetAf(float _a) { SetA(FloatToChar(_a)); }
		void SetRGBAf(float _rgba[4]) { SetRf(_rgba[0]); SetGf(_rgba[1]); SetBf(_rgba[2]); SetAf(_rgba[3]); }

		void SetColorCode(uint32_t _colorCode) { colorCode = _colorCode; }
	};
}

