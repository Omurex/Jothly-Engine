#include "Texture.h"


namespace jothly
{
	Texture::Texture()
	{
		backingTexture = raylib::rlb_Texture();
	}


	Texture::Texture(const std::string& loadPath)
	{
		backingTexture = raylib::rlb_Texture();
		LoadTexture(loadPath);
	}


	void Texture::LoadTexture(const std::string& loadPath)
	{
		backingTexture.Load(loadPath);
	}


	bool Texture::TryLoadTexture(const std::string& loadPath)
	{
		try
		{
			backingTexture.Load(loadPath);
			return true;
		}
		catch (std::exception e)
		{
			return false;
		}
	}
}