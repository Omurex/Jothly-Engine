#pragma once


#include "include/Texture.hpp"


class Texture
{
	raylib::rlb_Texture backingTexture;


	public:
	Texture();
	Texture(const std::string& loadPath);

	void LoadTexture(const std::string& loadPath);
	bool TryLoadTexture(const std::string& loadPath);

	raylib::rlb_Texture* GetBackingTexture() { return &backingTexture; }
};