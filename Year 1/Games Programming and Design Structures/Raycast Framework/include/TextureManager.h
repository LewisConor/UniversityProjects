#include <stdafx.h>
#pragma once

#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

//Foward Declaration
class Texture;

class TextureManager
{
public:
	#pragma region Constructor and Destructor
	TextureManager();
	~TextureManager();
	#pragma endregion

	//Get Instance
	static TextureManager* GetInstance() { return m_instance; }

	#pragma region Texture Functions
	bool TextureExists(const char* a_textureName);
	Texture* LoadTexture(const char* a_textureName, u32 a_format);
	Texture* GetTexture(const char* a_fileName);
	void ReleaseTexture(Texture* a_texturePointer);
	#pragma endregion

private:
	static TextureManager* m_instance;

	typedef struct TextureRef
	{
		Texture* pTexture;
		unsigned int refCount;
	}TextureRef;

	std::map<std::string, TextureRef> m_textureMap;
};

#endif //__TEXTURE_MANAGER_H__