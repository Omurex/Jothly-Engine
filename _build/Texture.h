#pragma once


#include "include/Texture.hpp"
#include "Vector2.h"


namespace jothly
{
	class Texture
	{
		raylib::rlb_Texture backingTexture;


	public:
		Texture();
		Texture(const std::string& loadPath);

		void LoadTexture(const std::string& loadPath);
		bool TryLoadTexture(const std::string& loadPath);

		raylib::rlb_Texture* GetBackingTexture() { return &backingTexture; }
		float GetWidth() { return backingTexture.GetWidth(); }
		float GetHeight() { return backingTexture.GetHeight(); }
		Vector2 GetSize() { return Vector2(backingTexture.GetSize()); }
	};
}