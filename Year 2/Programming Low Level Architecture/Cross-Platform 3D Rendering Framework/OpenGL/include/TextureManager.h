#pragma once

#include <map>
#include <string>

class Texture;

class TextureManager
{
public:
	static TextureManager* CreateInstance();
	static TextureManager* GetInstance();
	static void DestoryInstance();

	bool TextureExists(const char* a_Name);
	unsigned int LoadTexture(const char* a_filename);
	unsigned int GetTexture(const char* a_filename);

	void ReleaseTexture(unsigned int a_texture);

private:
	static TextureManager* m_instance;

	typedef struct TextureRef
	{
		Texture* pTexture;
		unsigned int refCount;
	}TextureRef;

	std::map<std::string, TextureRef> m_TextureMap;

	TextureManager();
	~TextureManager();
};